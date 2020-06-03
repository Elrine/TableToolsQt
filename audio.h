#ifndef TRACK_H
#define TRACK_H

#include <QUrl>
#include <list>
#include "fmod.hpp"
#include <QDomElement>

class AudioManager {
private:
    FMOD::System *system;
    static AudioManager m_instance;
    AudioManager();
    AudioManager& operator=(AudioManager const&);
public:
    FMOD::System *getSystem();
    static AudioManager &getAudioManager();
};

class Track
{
private:
    QString name;
    std::list<QString> tags;
    QUrl filepath;
    bool looping;
    float vol;
    FMOD::Sound *sound;
    FMOD::Channel *channel;
    static FMOD::System *system;
public:
    Track();
    Track(QString const& name, QUrl const& filepath = QUrl(""), bool looping = false);
    Track(Track const& src);
    ~Track();
    Track& operator=(Track const& src);
    QDomDocument *toXML() const;
    void loadXML(QDomElement const& xmlElement);
    void setName(QString const& name);
    void addTag(QString const& tag);
    void removeTag(QString const& tag);
    void setFilepath(QUrl const& filepath);
    void setLoop(bool loop);
    void setSoundPos(unsigned int pos);
    void setVolume(float vol);
    QString const& getName() const;
    std::list<QString> const& getTags() const;
    QUrl const& getFilepath() const;
    bool getLoop() const;
    unsigned int getSoundLength() const;
    unsigned int getPos() const;
    float getVol() const;
    void loadSound(QUrl const& projectPath);
    void play();
    void pause();
};

#endif // TRACK_H
