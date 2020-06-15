#ifndef TAGBLEDATA_H
#define TAGBLEDATA_H

#include <list>
#include <QString>

class TagbleData {
public:
    TagbleData() {};
    std::list<QString> const& getTags() const;
    void addTag(QString const& tag);
    void removeTag(QString const& tag);
protected:
    std::list<QString> tags;
};

#endif // TAGBLEDATA_H
