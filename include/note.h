#ifndef NOTE_H
#define NOTE_H

#include <QUrl>
#include <vector>
#include <QDomElement>
#include <QAbstractItemModel>
#include "tagbledata.h"

class Note : public TagbleData
{
private:
    QString name;
    QString content;
    std::vector<Note*> childs;
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
    bool addChildAt(Note *newChild, int row);
    void removeChild(Note* const child);
    void setParent(Note* const parent);
    QString const& getName() const;
    QString const& getContent() const;
    std::vector<Note*> const& getChilds() const;
    Note* getParent() const;
    Note *getChild(int row) const;
    int childCount() const;
};

class NoteModel : public QAbstractItemModel {
    Q_OBJECT

public:
    explicit NoteModel(std::list<Note *> const& data, QObject *parent = nullptr);
    ~NoteModel();

    QVariant data(QModelIndex const&index, int role) const override;
    Qt::ItemFlags flags(QModelIndex const& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
private:
    Note *rootItem;
};

#endif // NOTE_H
