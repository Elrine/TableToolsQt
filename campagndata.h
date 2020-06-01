#ifndef CAMPAGNDATA_H
#define CAMPAGNDATA_H

#include <QUrl>
#include <QFileInfo>
#include "note.h"

class CampagnData
{
private:
    QUrl path;
    QString name;
    std::list<Note*> listNote;

    void saveNotes() const;
    bool loadNotes();
    bool generateNotes() const;
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
    std::list<Note*> const& getNotes() const;
    QString const& getName() const;
};

#endif // CAMPAGNDATA_H
