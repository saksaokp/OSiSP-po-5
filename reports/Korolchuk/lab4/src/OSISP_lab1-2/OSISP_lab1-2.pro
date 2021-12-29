QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ball.cpp \
    dialogchoose.cpp \
    dialogstart.cpp \
    main.cpp \
    arkanoid.cpp \
    paddle.cpp

HEADERS += \
    arkanoid.h \
    ball.h \
    dialogchoose.h \
    dialogstart.h \
    paddle.h \
    pluginInterface.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-helper-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/release/ -lhelper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-helper-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/ -lhelper

INCLUDEPATH += $$PWD/../helper
DEPENDPATH += $$PWD/../helper

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-helper_class-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/release/ -lhelper_class
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-helper_class-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/ -lhelper_class

INCLUDEPATH += $$PWD/../helper_class
DEPENDPATH += $$PWD/../helper_class

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-about-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/release/ -labout
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-about-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/ -labout

INCLUDEPATH += $$PWD/../about
DEPENDPATH += $$PWD/../about
