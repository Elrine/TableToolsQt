#ifndef NOTE_H
#define NOTE_H

#include <QUrl>
#include <list>
#include <QDomElement>
#include "tagbledata.h"

class Note : public TagbleData
{
private:
    QString name;
    QString content;
    std::list<Note*> childs;
    Note* parent;
public:
    Note();
    Note(QString const& name, Note* parent = nullptr, QString const& content = "");
    Note(Note const& src);
    ~Note();
    Note& operator=(Note const& src);
    QDomDocument *toXML() const;
    void loadXML(QDomElement const& xmlElement);
    void setName(QString const& name);
    void setContent(QString const& content);
    bool addChild(Note* newChild);
    void removeChild(Note* const child);
    void setParent(Note* const parent);
    QString const& getName() const;
    QString const& getContent() const;
    std::list<Note*> const& getChilds() const;
    Note* getParent() const;
};

#endif // NOTE_H
