QT += gui

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fontPlugin.cpp

HEADERS += \
    fontPlugin.h

DEFINES += FONTPLUGIN_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

DISTFILES += fontPlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-fontPluginInterface2-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/release/ -lfontPluginInterface2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-fontPluginInterface2-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/debug/ -lfontPluginInterface2
else:unix: LIBS += -L$$PWD/../build-fontPluginInterface2-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/ -lfontPluginInterface2

INCLUDEPATH += $$PWD/../fontPluginInterface
DEPENDPATH += $$PWD/../fontPluginInterface
