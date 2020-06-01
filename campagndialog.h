#ifndef CAMPAGNDIALOG_H
#define CAMPAGNDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QUrl>

class CampagnDialog : public QDialog
{
    Q_OBJECT
public:
    CampagnDialog(QWidget *parent = nullptr);
public slots:
    bool selectCampagn();
    bool selectPath();
signals:
    void CampagnSelected(QUrl path);
    void PathSelected(QUrl path);
private:
    QPushButton *m_createButon;
    QPushButton *m_openButon;
};

#endif // CAMPAGNDIALOG_H
