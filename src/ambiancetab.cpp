#include "include/ambiancetab.h"
#include "ui_ambiancetab.h"

AmbianceTab::AmbianceTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AmbianceTab)
{
    ui->setupUi(this);
}

AmbianceTab::~AmbianceTab()
{
    delete ui;
}
