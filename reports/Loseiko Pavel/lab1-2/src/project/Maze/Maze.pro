QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    game.cpp \
    generator.cpp \
    main.cpp \
    maze.cpp \
    menu.cpp

HEADERS += \
    generator.h \
    maze.h

FORMS += \
    maze.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
