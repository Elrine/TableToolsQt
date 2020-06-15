#include "mainwindow.h"
#include "ambiancetab.h"
#include <QFileDialog>
#include <QUrl>
#include <QDebug>

MainWindow::MainWindow(CampagnData* _campagn, QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    campagn = _campagn;
    if (campagn != nullptr)
        initTab();
    connect(ui.action_Open, SIGNAL(triggered()), this, SLOT(openCampagn()));
    connect(ui.action_Create, SIGNAL(triggered()), this, SLOT(createCampagn()));
    connect(ui.action_Save, SIGNAL(triggered()), this, SLOT(save()));
}

MainWindow::~MainWindow()
{
    delete campagn;
    delete tabWidget;
}

void MainWindow::openCampagn() {
    QUrl filepath = QFileDialog::getExistingDirectoryUrl(this, tr("Open Campagn"), QDir::home().dirName());
    if (!filepath.isEmpty()) {
        this->campagn = CampagnData::initCampagn(filepath, true);
        initTab();
    }
}

void MainWindow::createCampagn() {
    QUrl filepath = QFileDialog::getExistingDirectoryUrl(this, tr("Create Campagn"), QDir::home().dirName());
    if (!filepath.isEmpty()) {
        this->campagn = CampagnData::initCampagn(filepath);
        initTab();
    }
}

void MainWindow::save() {
    campagn->save();
}

void MainWindow::initTab() {
    if (this->campagn == nullptr)
        return;
    tabWidget = new QTabWidget(ui.centralwidget);
    tabWidget->addTab(new AmbianceTab(campagn, tabWidget), tr("Ambiance"));
    ui.centralwidget->layout()->addWidget(tabWidget);
}
