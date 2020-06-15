#ifndef TRACKWIDGET_H
#define TRACKWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QSlider>
#include "audio.h"
#include "campagndata.h"
#include "tagwidget.h"
#include "ui_trackwidget.h"

class TrackWidget : public QWidget
{
    Q_OBJECT
    Track *trackData;
    CampagnData *campagnData;
    QThread *updateThread;
    bool isPlaying;

    void updatePositionLoop();
    Ui::TrackWidget ui;
public:
    explicit TrackWidget(Track* data, CampagnData *campagnData = nullptr, QWidget *parent = nullptr);

public slots:
    void playTrack();
    void pauseTrack();
    void onClickPlaying();
    void stopTrack();
    void changeVolume(int vol);
    void changePositon(int pos);
    void changeLoop(int loopStatus);
    void changeName(QString const& newName);
    void addTag();
    void removeTag(TagWidget *tag);
    void removeTrack();

signals:
    void PositionChanged(int pos);
};

#endif // TRACKWIDGET_H
