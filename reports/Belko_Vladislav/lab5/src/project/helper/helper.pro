QT += core gui
QT += widgets

TARGET = Helper
TEMPLATE = lib
DEFINES += HELPER_LIBRARY

CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    helper.cpp

HEADERS += \
    helper_global.h \
    helper.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
