#-------------------------------------------------
#
# Project created by QtCreator 2012-11-12T00:25:39
#
#-------------------------------------------------

QT       += core gui

QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Filippakoc_mechanic_pacman_demo
TEMPLATE = app

SOURCES += main.cpp\
        window.cpp \
    pacman.cpp \
    map.cpp \
    ball.cpp \
    ghost.cpp \
    powerball.cpp

HEADERS  += window.h \
    ball.h \
    pacman.h \
    map.h \
    ghost.h \
    powerball.h

FORMS    += window.ui

RESOURCES += \
    images.qrc

DISTFILES +=


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-helper_class-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/release/ -lhelper_class
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-helper_class-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/debug/ -lhelper_class
else:unix: LIBS += -L$$PWD/../build-helper_class-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/ -lhelper_class

INCLUDEPATH += $$PWD/../helper_class_global
DEPENDPATH += $$PWD/../helper_class_global


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../fontPlugin/build-fontPluginInterface-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/release/ -lfontPluginInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../fontPlugin/build-fontPluginInterface-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/debug/ -lfontPluginInterface
else:unix: LIBS += -L$$PWD/../fontPlugin/build-fontPluginInterface-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/ -lfontPluginInterface

INCLUDEPATH += $$PWD/../fontPlugin/fontPluginInterface
DEPENDPATH += $$PWD/../fontPlugin/fontPluginInterface
