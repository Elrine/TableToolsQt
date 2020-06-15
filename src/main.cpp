#include "mainwindow.h"
#include "trackwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CampagnData *campagnData = CampagnData::initCampagn(QUrl("FILE:///C:/Users/asus/Documents/0-TableToolsTest/test"), true);

    MainWindow w(campagnData);
//    Track *track = campagnData->getTracks().front();
//    TrackWidget widget(track);
//    widget.show();
//    campagnData->save();
    w.show();
    return a.exec();
}
