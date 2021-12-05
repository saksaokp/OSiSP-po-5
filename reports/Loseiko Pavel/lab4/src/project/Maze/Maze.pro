QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS
LIBS += -L./lHelper
LIBS += -L./About

INCLUDEPATH += ../interfaces
INCLUDEPATH += ../interfaces_theme

SOURCES += \
    game.cpp \
    generator.cpp \
    main.cpp \
    menu.cpp \
    maze.cpp

HEADERS += \ \
    about.h \
    about_global.h \
    helper.h \
    helper_global.h \
    maze.h


FORMS += \
    maze.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
