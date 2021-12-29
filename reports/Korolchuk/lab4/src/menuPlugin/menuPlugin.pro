QT += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = plugin1
TEMPLATE = lib
CONFIG += plugin
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

DESTDIR = ../Plugins

SOURCES += \
    menuPlugin.cpp

HEADERS += \
    menuPlugin.h \
    pluginInterface.h

DISTFILES += menuPlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
