#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "campagndata.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    bool openCampagn(QUrl filepath);
    bool createCampagn(QUrl filepath);
private:
    CampagnData *campagn;
};
#endif // MAINWINDOW_H
