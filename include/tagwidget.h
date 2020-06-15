#ifndef TAGWIDGET_H
#define TAGWIDGET_H

#include <QWidget>
#include "tagbledata.h"
#include "ui_tagwidget.h"


class TagWidget : public QWidget
{
    Q_OBJECT

    QString tagName;
public:
    explicit TagWidget(QString const& tagName, QWidget *parent = nullptr);
    ~TagWidget();
    QString const& getTag() const;
public slots:
    void removeTag();

signals:
    void tagRemoved(TagWidget*);

private:
    Ui::TagWidget *ui;
};

#endif // TAGWIDGET_H
