QT += core gui
QT += widgets

TARGET = LEVELS
TEMPLATE = lib
DEFINES += HELPER_LIBRARY

CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    levels.cpp \

HEADERS += \
    levels.h \
    levels_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
