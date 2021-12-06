QT += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = plugin2
TEMPLATE = lib
CONFIG += plugin
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

DESTDIR = ../Plugins

SOURCES += \
    menuPlugin2.cpp

HEADERS += \
    menuPlugin2.h \
    pluginInterface.h

DISTFILES += menuPlugin2.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
