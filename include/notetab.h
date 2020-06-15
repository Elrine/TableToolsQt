#ifndef NOTETAB_H
#define NOTETAB_H

#include <QWidget>

namespace Ui {
class NoteTab;
}

class NoteTab : public QWidget
{
    Q_OBJECT

public:
    explicit NoteTab(QWidget *parent = nullptr);
    ~NoteTab();

private:
    Ui::NoteTab *ui;
};

#endif // NOTETAB_H
