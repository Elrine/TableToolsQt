#include "tagbledata.h"

std::list<QString> const& TagbleData::getTags() const {
    return tags;
}


void TagbleData::addTag(const QString &tag) {
    if (std::count(this->tags.begin(), this->tags.end(), tag) == 0)
        this->tags.push_front(tag);
}

void TagbleData::removeTag(const QString &tag) {
    this->tags.remove(tag);
}
