#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "campagndata.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(CampagnData *campagn = nullptr, QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void openCampagn();
    void createCampagn();
    void save();
private:
    void initTab();
    QTabWidget *tabWidget;
    CampagnData *campagn;
    Ui::MainWindow ui;
};
#endif // MAINWINDOW_H
