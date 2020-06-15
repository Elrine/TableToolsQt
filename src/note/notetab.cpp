#include "include/notetab.h"
#include "ui_notetab.h"

NoteTab::NoteTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoteTab)
{
    ui->setupUi(this);
}

NoteTab::~NoteTab()
{
    delete ui;
}
