#include "audio.h"

AudioManager AudioManager::m_instance = AudioManager();

AudioManager::AudioManager() {
    FMOD::System_Create(&this->system);
    this->system->init(256, FMOD_INIT_NORMAL, nullptr);
}

AudioManager& AudioManager::operator=(const AudioManager &src) {
    this->system = src.system;
    return *this;
}

AudioManager &AudioManager::getAudioManager() {
    return AudioManager::m_instance;
}

FMOD::System *AudioManager::getSystem() {
    return this->system;
}

Track::Track()
{
    this->sound = nullptr;
    this->channel = nullptr;
    this->looping = false;
    this->vol = 1;
}

Track::Track(QString const& name, QString const& filepath, bool looping) {
    this->name = name;
    this->looping = looping;
    this->vol = 1;
    this->sound = nullptr;
    this->channel = nullptr;
    this->setFilepath(filepath);
}

Track::Track(Track const& src) {
    this->name = src.name;
    this->looping = src.looping;
    this->vol = src.vol;
    this->sound = nullptr;
    this->channel = nullptr;
    this->setFilepath(src.filepath);
}

Track::~Track() {
    if (this->sound != nullptr) {
        this->sound->release();
    }
    if (this->channel != nullptr) {
        this->channel->stop();
    }
}

Track& Track::operator=(Track const& src) {
    this->name = src.name;
    this->looping = src.looping;
    this->vol = src.vol;
    this->sound = nullptr;
    this->channel = nullptr;
    this->setFilepath(src.filepath);
    return *this;
}

QDomDocument *Track::toXML() const {
    QDomDocument *dom = new QDomDocument();
    QDomElement el = dom->createElement("Track");

    el.setAttribute("Name", this->name);
    el.setAttribute("Loop", this->looping ? "True" : "False");
    el.setAttribute("Volume", this->vol);
    dom->appendChild(el);
    QDomElement filepath;
    filepath = dom->createElement("Path");
    filepath.appendChild(dom->createTextNode(this->filepath));
    el.appendChild(filepath);
    if (this->tags.size() > 0) {
        QDomElement tags;
        tags = dom->createElement("Tags");
        for (std::list<QString>::const_iterator tag = this->tags.begin(); tag != this->tags.end(); ++tag) {
            QDomElement el_tag;
            el_tag = dom->createElement("Tag");
            el_tag.appendChild(dom->createTextNode(*tag));
            tags.appendChild(el_tag);
        }
        el.appendChild(tags);
    }
    return dom;
}

void Track::loadXML(const QDomElement &xmlElement) {
    this->name = xmlElement.attribute("Name");
    this->looping = xmlElement.attribute("Loop") == "True";
    this->vol = xmlElement.attribute("Volume").toFloat();
    QDomElement componant = xmlElement.firstChild().toElement();
    while (!componant.isNull()) {
        if (componant.tagName() == "Path") {
            this->setFilepath(componant.firstChild().toText().data());
        }
        else if (componant.tagName() == "Tags") {
            QDomElement tagComponant = componant.firstChild().toElement();
            while(!tagComponant.isNull()) {
                if (tagComponant.tagName() == "Tag") {
                    this->addTag(tagComponant.firstChild().toText().data());
                }
                tagComponant = tagComponant.nextSibling().toElement();
            }
        }
        componant = componant.nextSibling().toElement();
    }
}

void Track::setName(const QString &name) {
    this->name = name;
}

void Track::setFilepath(const QString &filepath) {
    this->filepath = filepath;
}

void Track::setLoop(bool loop) {
    if (this->looping != loop) {
        this->looping = loop;
        if (this->channel != nullptr) {
            this->channel->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
        }
        else if (this->sound != nullptr) {
            this->sound->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
        }
    }
}

void Track::setSoundPos(unsigned int pos) {
    if (this->channel != nullptr) {
        this->channel->setPosition(pos, FMOD_TIMEUNIT_MS);
    }
}

void Track::setVolume(float vol) {
    this->vol = vol;
    if (this->channel != nullptr) {
        this->channel->setVolume(vol);
    }
}

QString const& Track::getName() const {
    return this->name;
}

QString const& Track::getFilepath() const {
    return this->filepath;
}

bool Track::getLoop() const {
    return this->looping;
}

bool Track::isPlaying() const {
    bool isPlaying = false;
    bool isPaused = false;
    if (this->channel != nullptr) {
        this->channel->isPlaying(&isPlaying);
        this->channel->getPaused(&isPaused);
    }
    return isPlaying && !isPaused;
}

unsigned int Track::getSoundLength() const {
    if (this->sound == nullptr)
        return 0;
    unsigned int length;
    this->sound->getLength(&length, FMOD_TIMEUNIT_MS);
    return length;
}

unsigned int Track::getPos() const {
    if (this->channel == nullptr)
        return 0;
    unsigned int pos;
    this->channel->getPosition(&pos, FMOD_TIMEUNIT_MS);
    return pos;
}

float Track::getVol() const {
    return this->vol;
}

void Track::loadSound(const QUrl &projectPath) {
    QUrl truePath = projectPath.resolved(this->filepath);
    AudioManager::getAudioManager().getSystem()->createSound(
                truePath.toLocalFile().toStdString().c_str(),
                this->looping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF,
                nullptr,
                &this->sound);
}

void Track::play() {
    if (this->sound == nullptr) {
        return;
    }
    if (this->channel == nullptr) {
        AudioManager::getAudioManager().getSystem()->playSound(
                    this->sound,
                    nullptr,
                    false,
                    &this->channel);
        this->channel->setVolume(this->vol);
    }
    else {
        this->channel->setPaused(false);
    }
}

void Track::pause() {
    if (this->channel == nullptr) {
        return;
    }
    this->channel->setPaused(true);
}

void Track::stop() {

    if (this->channel == nullptr) {
        return;
    }
    this->channel->stop();
    this->channel = nullptr;
}
