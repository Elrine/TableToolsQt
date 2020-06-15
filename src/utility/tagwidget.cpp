#include "include\tagwidget.h"
#include "ui_tagwidget.h"

TagWidget::TagWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagWidget)
{
    ui->setupUi(this);
}

TagWidget::~TagWidget()
{
    delete ui;
}
