#include "include\tagwidget.h"
#include "ui_tagwidget.h"

TagWidget::TagWidget(QString const& _tagName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagWidget)
{
    ui->setupUi(this);
    tagName = _tagName;
    ui->TagName->setText(tagName);
    connect(ui->DeleteTag, SIGNAL(clicked()), this, SLOT(removeTag()));
}

TagWidget::~TagWidget()
{
    delete ui;
}

QString const& TagWidget::getTag() const {
    return tagName;
}

void TagWidget::removeTag() {
    emit tagRemoved(this);
}

