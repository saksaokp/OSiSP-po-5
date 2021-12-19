QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS
LIBS +=./release/Helper.dll
LIBS +=./release/About.dll
INCLUDEPATH += ../interfaces
INCLUDEPATH += ../interfaces_theme

SOURCES += \
    main.cpp \
    player.cpp \
    thread.cpp

HEADERS += \
    about.h \
    about_global.h \
    helper.h \
    helper_global.h \
    player.h \
    thread.h

FORMS += \
    player.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
