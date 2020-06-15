#ifndef TAGWIDGET_H
#define TAGWIDGET_H

#include <QWidget>

namespace Ui {
class TagWidget;
}

class TagWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TagWidget(QWidget *parent = nullptr);
    ~TagWidget();

private:
    Ui::TagWidget *ui;
};

#endif // TAGWIDGET_H
