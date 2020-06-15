#include "note.h"
#include <algorithm>

Note::Note()
{
}

Note::Note(QString const& name, Note* parent, QString const& content) {
    this->name = name;
    this->content = content;
    this->parent = parent;
    if (parent != nullptr)
        parent->childs.push_front(this);
}

Note::Note(Note const& src) {
    this->name = src.getName();
    this->content = src.getContent();
    std::list<QString> const srcTags = src.getTags();
    for(std::list<QString>::const_iterator tag = srcTags.begin(); tag != srcTags.end(); ++tag) {
        this->tags.push_back(*tag);
    }
}

Note::~Note() {
    while (!this->tags.empty()) {
        this->tags.pop_back();
    }
    while (!this->childs.empty()) {
        delete this->childs.back();
        this->childs.pop_back();
    }
}

Note& Note::operator=(const Note &src) {
    this->name = src.getName();
    this->content = src.getContent();
    std::list<QString> const srcTags = src.getTags();
    for(std::list<QString>::const_iterator tag = srcTags.begin(); tag != srcTags.end(); ++tag) {
        this->tags.push_back(*tag);
    }
    std::list<Note*> const srcChilds = src.getChilds();
    for(std::list<Note*>::const_iterator child = srcChilds.begin(); child != srcChilds.end(); ++child) {
        this->childs.push_back(*child);
    }
    return *this;
}

QDomDocument* Note::toXML() const {
    QDomDocument *dom = new QDomDocument();
    QDomElement el = dom->createElement("Note");

    el.setAttribute("Name", this->name);
    dom->appendChild(el);
    if (this->content != "") {
        QDomElement content;
        content = dom->createElement("Content");
        content.appendChild(dom->createTextNode(this->content));
        el.appendChild(content);
    }
    if (this->tags.size() > 0) {
        QDomElement tags;
        tags = dom->createElement("Tags");
        for (std::list<QString>::const_iterator tag = this->tags.begin(); tag != this->tags.end(); ++tag) {
            QDomElement el_tag;
            el_tag.setTagName("Tag");
            el_tag.setNodeValue(*tag);
            tags.appendChild(el_tag);
        }
        el.appendChild(tags);
    }
    if (this->childs.size() > 0) {
        QDomElement childs;
        childs = dom->createElement("Childs");
        QDomDocument *el_note;
        for (std::list<Note*>::const_iterator child = this->childs.begin(); child != this->childs.end(); ++child) {
            el_note = (*child)->toXML();
            childs.appendChild(el_note->firstChild());
            delete el_note;
        }
        el.appendChild(childs);
    }
    return dom;
}

void Note::loadXML(const QDomElement &xmlElement) {
    this->name = xmlElement.attribute("Name");
    QDomElement componant = xmlElement.firstChild().toElement();
    while (!componant.isNull()) {
        if (componant.tagName() == "Content") {
            this->content = componant.firstChild().toText().data();
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
        else if (componant.tagName() == "Childs") {
            QDomElement childComponant = componant.firstChild().toElement();
            while(!childComponant.isNull()) {
                if (childComponant.tagName() == "Note") {
                    Note *newNote;
                    newNote = new Note();
                    newNote->loadXML(childComponant);
                    newNote->parent = this;
                    this->addChild(newNote);
                }
                childComponant = childComponant.nextSibling().toElement();
            }
        }
        componant = componant.nextSibling().toElement();
    }
}

void Note::setName(const QString &name) {
    this->name = name;
}

void Note::setContent(const QString &content) {
    this->content = content;
}


bool Note::addChild(Note* newChild) {
    for (std::list<Note*>::const_iterator child = this->childs.begin(); child != this->childs.end(); ++child) {
        if ((*child)->name == newChild->name)
            return false;
    }
    this->childs.push_front(newChild);
    return true;
}

void Note::removeChild(Note* const child) {
    this->childs.remove(child);
}

void Note::setParent(Note *const parent) {
    this->parent->removeChild(this);
    if (parent != nullptr)
        parent->addChild(this);
    this->parent = parent;
}

QString const& Note::getName() const {
    return this->name;
}

QString const& Note::getContent() const {
    return this->content;
}

std::list<Note*> const& Note::getChilds() const {
    return this->childs;
}

Note* Note::getParent() const {
    return this->parent;
}
