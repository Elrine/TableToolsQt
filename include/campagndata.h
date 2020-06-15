#ifndef CAMPAGNDATA_H
#define CAMPAGNDATA_H

#include <QUrl>
#include <QFileInfo>
#include "note.h"
#include "audio.h"

class CampagnData
{
private:
    QUrl path;
    QString name;
    std::list<Note*> listNote;
    std::list<Track*> listTrack;

    void saveNotes() const;
    bool loadNotes();
    bool generateNotes() const;

    void saveTracks() const;
    bool loadTracks();
    bool generateTracks() const;
public:
    CampagnData() = delete;
    explicit CampagnData(QUrl const& path, QString const& name);
    CampagnData(const CampagnData&);
    ~CampagnData();
    CampagnData& operator=(const CampagnData&);
    static CampagnData* initCampagn(QUrl const& path, bool loadCampagn = false);
    void generate() const;
    void save() const;
    void saveAs(QUrl const& newPath, QString const& newName = "");
    bool load();
    Note* createNote(QString const& name, Note* parent = nullptr, QString const& content = "");
    void deleteNote(Note* note);
    Track* importSound(QUrl const& filename);
    Track* createTrack(QString const& name, QString const& filename);
    void deleteTrack(Track* note);
    std::list<Note*> const& getNotes() const;
    std::list<Track*> const& getTracks() const;
    QString const& getName() const;
};

#endif // CAMPAGNDATA_H
