#ifndef AMBIANCETAB_H
#define AMBIANCETAB_H

#include <QWidget>
#include "campagndata.h"
#include "trackwidget.h"
#include "ui_ambiancetab.h"

class AmbianceTab : public QWidget
{
    Q_OBJECT
    CampagnData *data;
    Ui::AmbianceTab ui;
public:
    explicit AmbianceTab(CampagnData *_data, QWidget *parent = nullptr);

public slots:
    void addTrack();
signals:

};

#endif // AMBIANCETAB_H
