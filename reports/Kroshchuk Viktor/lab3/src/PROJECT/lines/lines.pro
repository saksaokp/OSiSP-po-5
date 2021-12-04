QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
LIBS +=./release/Helper.dll
LIBS +=./release/About.dll
INCLUDEPATH += ../interfaces


# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameLogic.cpp \
    Ghost.cpp \
    cell.cpp \
    main.cpp \
    mainwindow.cpp \
    startscreen.cpp

HEADERS += \
    Definitions.h \
    GameLogic.h \
    Ghost.h \
    about.h \
    about_global.h \
    cell.h \
    helper.h \
    helper_global.h \
    mainwindow.h \
    startscreen.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Assets/ConcertOne-Regular.ttf \
    Assets/background.png \
    Assets/blocker.png \
    Assets/button_highscore.png \
    Assets/button_home.png \
    Assets/button_pause.png \
    Assets/button_play.png \
    Assets/cell_dark.png \
    Assets/cell_light.png \
    Assets/cell_selected.png \
    Assets/creativity.png \
    Assets/ghost_green.png \
    Assets/ghost_red.png \
    Assets/ghost_white.png \
    Assets/ghost_yellow.png \
    Assets/icon.ico \
    Assets/icon_path.png \
    Assets/panel_objectives.png \
    Assets/preview_1.png \
    Assets/preview_2.png \
    Assets/restart_button.png \
    Assets/splash.png \
    Assets/update.png

RESOURCES += \
    assets.qrc
