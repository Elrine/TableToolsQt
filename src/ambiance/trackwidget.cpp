#include "trackwidget.h"
#include "tagwidget.h"
#include <QInputDialog>
#include <QThread>
#include <QStyle>

TrackWidget::TrackWidget(Track* data, CampagnData* _campagnData, QWidget *parent) : QWidget(parent)
{
    this->isPlaying = false;
    this->ui.setupUi(this);
    this->updateThread = nullptr;
    this->trackData = data;
    campagnData = _campagnData;

    ui.trackName->setText(data->getName());
    this->ui.loopBox->setCheckState(this->trackData->getLoop() ? Qt::Checked : Qt::Unchecked);

    this->ui.volSlider->setValue(this->trackData->getVol() * 100);

    this->ui.posSlider->setRange(0, this->trackData->getSoundLength());

    std::list<QString> tags = data->getTags();
    for (std::list<QString>::const_iterator tag = tags.begin(); tag != tags.end(); ++tag) {
        TagWidget *tagWidget = new TagWidget(*tag, ui.tagList);
        ui.tagList->layout()->addWidget(tagWidget);
        connect(tagWidget, SIGNAL(tagRemoved(TagWidget*)), this, SLOT(removeTag(TagWidget*)));
    }

    if (campagnData != nullptr)
        connect(ui.deleteButton, SIGNAL(clicked()), this, SLOT(removeTrack()));
    else
        ui.deleteButton->deleteLater();
    connect(this->ui.playButton, SIGNAL(clicked()), this, SLOT(onClickPlaying()));
    connect(this->ui.stopButton, SIGNAL(clicked()), this, SLOT(stopTrack()));
    connect(ui.addTag, SIGNAL(clicked()), this, SLOT(addTag()));
    connect(this->ui.loopBox, SIGNAL(stateChanged(int)), this, SLOT(changeLoop(int)));
    connect(this->ui.volSlider, SIGNAL(valueChanged(int)), this, SLOT(changeVolume(int)));
    connect(this->ui.posSlider, SIGNAL(sliderMoved(int)), this, SLOT(changePositon(int)));
    connect(this, SIGNAL(PositionChanged(int)), this->ui.posSlider, SLOT(setValue(int)));
}

void TrackWidget::updatePositionLoop() {
    unsigned int pos = this->trackData->getPos();
    while (this->trackData->isPlaying()) {
        emit this->PositionChanged(pos);
        QThread::msleep(100);
        pos = this->trackData->getPos();
    }
    this->isPlaying = false;
}

void TrackWidget::playTrack() {
    if (this->isPlaying)
        return;
    if (this->updateThread != nullptr) {
        this->updateThread->terminate();
        delete this->updateThread;
    }
    this->trackData->play();
    this->updateThread = QThread::create(&TrackWidget::updatePositionLoop, this);
    this->isPlaying = true;
    this->updateThread->start();
    this->ui.playButton->setText("Pause");
}

void TrackWidget::pauseTrack() {
    if (!this->isPlaying)
        return;
    this->trackData->pause();
    this->ui.playButton->setText("Play");
}

void TrackWidget::onClickPlaying() {
    if (this->isPlaying) {
        this->pauseTrack();
    } else {
        this->playTrack();
    }
}

void TrackWidget::stopTrack() {
    this->trackData->stop();
}

void TrackWidget::changeVolume(int vol) {
    this->trackData->setVolume(vol/(float)100);
}

void TrackWidget::changePositon(int pos) {
    unsigned int newPos = static_cast<unsigned int>(pos);
    this->trackData->setSoundPos(newPos);
}

void TrackWidget::changeLoop(int loopStatus) {
    this->trackData->setLoop(loopStatus == Qt::Checked);
}

void TrackWidget::changeName(QString const& newName) {
    ui.trackName->setText(newName);
    trackData->setName(newName);
}

void TrackWidget::addTag() {
    bool ok;
    QString newTag = QInputDialog::getText(this, "New tag", "name of the new tag", QLineEdit::Normal,
                                           "", &ok);
    if (ok && !newTag.isEmpty()) {
        trackData->addTag(newTag);
        TagWidget *tagWidget = new TagWidget(newTag, ui.tagList);
        ui.tagList->layout()->addWidget(tagWidget);
        connect(tagWidget, SIGNAL(tagRemoved(TagWidget*)), this, SLOT(removeTag(TagWidget*)));
    }
}

void TrackWidget::removeTag(TagWidget* tag) {
    ui.tagList->layout()->removeWidget(tag);
    trackData->removeTag(tag->getTag());
    delete tag;
}

void TrackWidget::removeTrack() {
    stopTrack();
    this->updateThread->terminate();
    delete this->updateThread;
    campagnData->deleteTrack(this->trackData);
    parentWidget()->layout()->removeWidget(this);
    delete this;
}
