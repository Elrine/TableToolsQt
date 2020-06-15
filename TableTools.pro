QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

SOURCES += \
    src/ambiance/trackwidget.cpp \
    src/ambiance/ambiancetab.cpp \
    src/data/audio.cpp \
    src/data/campagndata.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/data/note.cpp \
    src/note/notetab.cpp \
    src/utility/tagbledata.cpp \
    src/utility/tagwidget.cpp


HEADERS += \
    include/notetab.h \
    include/tagbledata.h \
    include/ambiancetab.h \
    include/audio.h \
    include/campagndata.h \
    include/mainwindow.h \
    include/note.h \
    include/tagwidget.h \
    include/trackwidget.h

TRANSLATIONS += \
    TableTools_fr_FR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../../Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/core/lib/x64' -lfmod_vc
win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../../Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/core/lib/x64' -lfmodL_vc

INCLUDEPATH += $$PWD/'../../../../Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/core/inc'
DEPENDPATH += $$PWD/'../../../../Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/core/inc'

FORMS += \
    design/ambiancetab.ui \
    design/mainwindow.ui \
    design/notetab.ui \
    design/tagwidget.ui \
    design/trackwidget.ui

