QT += gui
QT += core

TEMPLATE = lib
DEFINES += MODE_LIBRARY
TARGET = Mode1

CONFIG += plugin
DESTDIR = ../calc_1/release/plugins
INCLUDEPATH += ../interfaces

DEFINES += QT_DEPRECATED_WARNINGS
DISTFILES += Interface.json

SOURCES += \
    mode.cpp

HEADERS += \
    mode.h

unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
