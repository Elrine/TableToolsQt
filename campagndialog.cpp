#include "campagndialog.h"
#include <QFileDialog>

CampagnDialog::CampagnDialog(QWidget *parent)
    : QDialog(parent)
{
    m_createButon = new QPushButton("Créer une campagne", this);
    m_openButon = new QPushButton("Ouvrir une campagne", this);
    QObject::connect(m_createButon, SIGNAL(clicked()), this, SLOT(selectPath()));
    QObject::connect(m_openButon, SIGNAL(clicked()), this, SLOT(selectCampagn()));
}

bool CampagnDialog::selectCampagn() {
    QUrl campagnUrl = QFileDialog::getExistingDirectoryUrl();
    if(campagnUrl.isEmpty()) {
        emit this->CampagnSelected(campagnUrl);
        return true;
    }
    else
        return false;
}

bool CampagnDialog::selectPath() {
    QUrl pathUrl = QFileDialog::getExistingDirectoryUrl();
    if (!pathUrl.isEmpty()) {
        emit this->PathSelected(pathUrl);
        return true;
    }
    else
        return false;
}
