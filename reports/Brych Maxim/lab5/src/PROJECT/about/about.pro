QT += core gui
QT += widgets

TARGET = About
TEMPLATE = lib
DEFINES += ABOUT_LIBRARY

CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    about.cpp

HEADERS += \
    about_global.h \
    about.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
