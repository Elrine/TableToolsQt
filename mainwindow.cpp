#include "mainwindow.h"
#include <QUrl>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->dialog = new CampagnDialog();
    this->dialog->show();
    QObject::connect(dialog, SIGNAL(CampagnSelected(QUrl)), this, SLOT(openCampagn(QUrl)));
    QObject::connect(dialog, SIGNAL(PathSelected(QUrl)), this, SLOT(createCampagn(QUrl)));
}

MainWindow::~MainWindow()
{
}

bool MainWindow::openCampagn(QUrl filepath) {
    this->campagn = CampagnData::initCampagn(filepath, true);
    qDebug() << "campagn OK?:" << (this->campagn != nullptr);
    delete this->dialog;
    return this->campagn != nullptr;
}

bool MainWindow::createCampagn(QUrl filepath) {
    this->campagn = CampagnData::initCampagn(filepath);
    qDebug() << "campagn OK?:" << (this->campagn != nullptr);
    delete this->dialog;
    return this->campagn != nullptr;
}
