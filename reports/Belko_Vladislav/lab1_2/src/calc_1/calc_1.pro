QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
LIBS += "C:\Users\Bululu\Documents\calc_1\debug\debug\helper.dll"
LIBS += "C:\Users\Bululu\Documents\calc_1\debug\debug\about.dll"
INCLUDEPATH += ../interfaces

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    helper.h \
    Helper_global.h \
    about.h \
    about_global.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
