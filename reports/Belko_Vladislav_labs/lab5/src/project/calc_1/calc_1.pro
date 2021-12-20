QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS
LIBS +=./release/Helper.dll
LIBS +=./release/About.dll
INCLUDEPATH += ../interfaces
INCLUDEPATH += ../interfaces_theme

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    thread.cpp

HEADERS += \
    about.h \
    about_global.h \
    helper.h \
    helper_global.h \
    mainwindow.h \
    helper.h \
    Helper_global.h \
    about.h \
    about_global.h \
    thread.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
