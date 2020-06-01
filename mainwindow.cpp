#include "mainwindow.h"
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

MainWindow::~MainWindow()
{
}

bool MainWindow::openCampagn(QUrl filepath) {
    this->campagn = CampagnData::initCampagn(filepath, true);
    return this->campagn != nullptr;
}

bool MainWindow::createCampagn(QUrl filepath) {
    this->campagn = CampagnData::initCampagn(filepath);
    return this->campagn != nullptr;
}
