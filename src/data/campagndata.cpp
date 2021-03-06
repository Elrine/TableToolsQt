#include "campagndata.h"
#include <QInputDialog>
#include <QDir>
#include <QDebug>
#include <QSaveFile>
#include <QDate>

CampagnData::CampagnData(QUrl const& path, QString const& name) {
    this->path = path;
    this->name = name;
}

CampagnData::CampagnData(CampagnData const& src) {
    this->path = src.path;
    this->name = src.name;
    for(std::vector<Note*>::const_iterator note = src.listNote.begin(); note != src.listNote.end(); ++note) {
        this->listNote.push_back(new Note(*(*note)));
    }
    for(std::vector<Track*>::const_iterator track = src.listTrack.begin(); track != src.listTrack.end(); ++track) {
        this->listTrack.push_back(new Track(*(*track)));
    }
}

CampagnData::~CampagnData() {
    while(!this->listNote.empty()){
        delete this->listNote.back();
        this->listNote.pop_back();
    }
}

CampagnData& CampagnData::operator=(CampagnData const& src) {
    this->path = src.path;
    this->name = src.name;
    for(std::vector<Note*>::const_iterator note = src.listNote.begin(); note != src.listNote.end(); ++note) {
        this->listNote.push_back(new Note(*(*note)));
    }
    for(std::vector<Track*>::const_iterator track = src.listTrack.begin(); track != src.listTrack.end(); ++track) {
        this->listTrack.push_back(new Track(*(*track)));
    }
    return *this;
}

CampagnData* CampagnData::initCampagn(QUrl const& path, bool loadCampagn) {
    QString name;
    CampagnData* campagn;
    if (!loadCampagn) {
        bool ok;
        name = QInputDialog::getText(nullptr, "Nom de Campagne", "Quelle nom de campagne?", QLineEdit::Normal, "", &ok);
        if (!ok || name.isEmpty())
            return nullptr;
        campagn = new CampagnData(path, name);
        campagn->generate();
    }
    else {
        name = path.fileName();
        QUrl adjustedPath = path.adjusted(QUrl::RemoveFilename);
        campagn = new CampagnData(adjustedPath, name);
        if (!campagn->load()) {
            delete campagn;
            return nullptr;
        }
    }
    return campagn;
}

void CampagnData::generate() const {
    QDir dir(this->path.toLocalFile());
    dir.mkdir(this->name);
    dir.cd(this->name);
    if (this->generateNotes()) {
        dir.mkdir("Ressource");
        dir.mkdir("Maps");
        dir.mkdir("Character");
        dir.mkdir("Track");
        dir.cd("Ressource");
        dir.mkdir("Music");
        dir.mkdir("Image");
        dir.cd("../Character");
        dir.mkdir("Template");
        dir.mkdir("Sheet");
    }
    else {
        dir.cdUp();
        dir.remove(this->name);
    }
}

bool CampagnData::generateNotes() const {
    QFile file(this->path.toLocalFile() + "/" + this->name + "/Notes.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::NewOnly)) {
        qDebug() << "Can't generate the Notes.xml file";
        return false;
    }
    QTextStream stream(&file);
    QDomDocument dom;
    QDomElement xmlDoc = dom.createElement("Notes");
    dom.appendChild(xmlDoc);
    xmlDoc.save(stream, 4, QDomDocument::EncodingFromDocument);
    file.close();
    return true;
}

bool CampagnData::generateTracks() const {
    QFile file(this->path.toLocalFile() + "/" + this->name + "/Tracks.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::NewOnly)) {
        qDebug() << "Can't generate the Tracks.xml file";
        return false;
    }
    QTextStream stream(&file);
    QDomDocument dom;
    QDomElement xmlDoc = dom.createElement("Tracks");
    dom.appendChild(xmlDoc);
    xmlDoc.save(stream, 4, QDomDocument::EncodingFromDocument);
    file.close();
    return true;
}

void CampagnData::saveNotes() const{
        QString path = this->path.toLocalFile() + "/" + this->name + "/Notes.xml";
        QSaveFile file(path);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
            return;
        QTextStream stream(&file);
        QDomDocument dom;
        QDomElement xmlDoc;
        xmlDoc = dom.createElement("Notes");
        QDomDocument *noteXml;
        foreach (Note* note, this->listNote) {
            noteXml = note->toXML();
            xmlDoc.appendChild(noteXml->firstChild());
            delete noteXml;
        }
        xmlDoc.save(stream, 4);
        file.commit();
}

void CampagnData::saveTracks() const{
        QString path = this->path.toLocalFile() + "/" + this->name + "/Tracks.xml";
        QSaveFile file(path);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
            return;
        QTextStream stream(&file);
        QDomDocument dom;
        QDomElement xmlDoc;
        xmlDoc = dom.createElement("Tracks");
        QDomDocument *trackXml;
        foreach (Track* track, this->listTrack) {
            trackXml = track->toXML();
            xmlDoc.appendChild(trackXml->firstChild());
            delete trackXml;
        }
        xmlDoc.save(stream, 4);
        file.commit();
}

void CampagnData::save() const {
    this->saveNotes();
    this->saveTracks();
}

void CampagnData::saveAs(const QUrl &newPath, const QString &newName) {
    if (newName != "")
        this->name = newName;
    this->path = newPath;
    this->generate();
    this->save();
}

bool CampagnData::loadNotes() {
    QDomDocument noteXml;
    QFile file(this->path.toLocalFile() + "/" + this->name + "/Notes.xml");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "file \"Notes.xml\" in \""<< this->path.toLocalFile() + "/" + this->name  <<"\" can't be loaded";
        return false;
    }
    QDomDocument xml;
    xml.setContent(&file);
    file.close();
    QDomElement root = xml.documentElement();
    QDomElement componant = root.firstChild().toElement();
    Note *note;
    while (!componant.isNull()) {
        if (componant.tagName() == "Note") {
            note = new Note();
            note->loadXML(componant);
            this->listNote.push_back(note);
        }
        componant = componant.nextSibling().toElement();
    }
    return true;
}

bool CampagnData::loadTracks() {
    QDomDocument noteXml;
    QFile file(this->path.toLocalFile() + "/" + this->name + "/Tracks.xml");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "file \"Tracks.xml\" in \""<< this->path.toLocalFile() + "/" + this->name  <<"\" can't be loaded";
        return false;
    }
    QDomDocument xml;
    xml.setContent(&file);
    file.close();
    QDomElement root = xml.documentElement();
    QDomElement componant = root.firstChild().toElement();
    Track *track;
    while (!componant.isNull()) {
        if (componant.tagName() == "Track") {
            track = new Track();
            track->loadXML(componant);
            this->listTrack.push_back(track);
            track->loadSound(this->path.resolved(this->name + "/"));
        }
        componant = componant.nextSibling().toElement();
    }
    return true;
}

bool CampagnData::load() {
    bool returnValue = true;
    returnValue = returnValue && this->loadNotes();
    returnValue = returnValue && this->loadTracks();
    return returnValue;
}

Note* CampagnData::createNote(const QString &name, Note *parent, const QString &content) {
    Note *note = new Note(name, parent, content);
    if (parent == nullptr)
        this->listNote.push_back(note);
    return note;
}

void CampagnData::deleteNote(Note *note) {
    Note* parentNote = note->getParent();
    if (parentNote == nullptr) {
        std::vector<Note*>::const_iterator it = std::find(listNote.begin(), listNote.end(), note);
        if (*it == note)
            this->listNote.erase(it);
    }
    else {
        parentNote->removeChild(note);
    }
    delete note;
}

Track* CampagnData::importSound(const QUrl &filename) {
    QString relativeFileDest = "./Ressource/Music/" + filename.fileName();
    QUrl projectPath = this->path.resolved(this->name + "/");
    QUrl resolvedPath = projectPath.resolved(relativeFileDest);
    qDebug() << "Copy from" << filename.toLocalFile() << "to" << resolvedPath.toLocalFile();
    if (QFile::exists(resolvedPath.toLocalFile()))
        QFile::remove(resolvedPath.toLocalFile());
    QFile::copy(filename.toLocalFile(), resolvedPath.toLocalFile());
    QFileInfo fileInfo(resolvedPath.toLocalFile());
    QString trackName = fileInfo.fileName().remove(QRegExp("\.[^\.]+$"));
    qDebug() << trackName;
    return this->createTrack(trackName, relativeFileDest);
}

Track* CampagnData::createTrack(const QString &name, const QString &filename) {
    Track *track = new Track(name, filename);
    this->listTrack.push_back(track);
    track->loadSound(this->path.resolved(this->name + "/"));
    return track;
}

void CampagnData::deleteTrack(Track *track) {
    std::vector<Track*>::const_iterator it = std::find(listTrack.begin(), listTrack.end(), track);
    if (*it == track)
        this->listTrack.erase(it);
    delete track;
}

std::vector<Note*> const& CampagnData::getNotes() const {
    return this->listNote;
}

std::vector<Track*> const& CampagnData::getTracks() const {
    return this->listTrack;
}

QString const& CampagnData::getName() const {
    return this->name;
}
