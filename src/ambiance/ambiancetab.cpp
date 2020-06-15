#include "ambiancetab.h"
#include "trackwidget.h"
#include <QFileDialog>

AmbianceTab::AmbianceTab(CampagnData* _data, QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    data = _data;
    std::list<Track*> tracks = data->getTracks();
    for (auto const& track : tracks) {
        TrackWidget *newTrack = new TrackWidget(track, data, ui.trackList->widget());
        ui.trackList->addWidget(newTrack);
    }
    connect(ui.addTrack, SIGNAL(clicked()), this, SLOT(addTrack()));
}


void AmbianceTab::addTrack() {
    QUrl filepath = QFileDialog::getOpenFileUrl(this);
    if (!filepath.isEmpty()) {
        Track* newTrack = data->importSound(filepath);
        TrackWidget* newWidget = new TrackWidget(newTrack, data, ui.trackList->widget());
        ui.trackList->addWidget(newWidget);
    }
}
