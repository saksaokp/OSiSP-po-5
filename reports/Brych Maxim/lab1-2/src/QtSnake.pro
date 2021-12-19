#-------------------------------------------------
#
# Project created by QtCreator 2015-05-31T10:41:23
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtSnake
TEMPLATE = app

SOURCES += main.cpp \
    food.cpp \
    game.cpp \
    menu.cpp \
    snake.cpp

HEADERS  += \
    include/about/about.h \
    include/about/about_global.h \
    snake.h

FORMS += \
    snake.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/include/about/release/ -labout
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/include/about/debug/ -labout
else:unix: LIBS += -L$$PWD/include/about/ -labout

INCLUDEPATH += $$PWD/include/about
DEPENDPATH += $$PWD/include/about

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/include/helper/release/ -lhelper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/include/helper/debug/ -lhelper
else:unix: LIBS += -L$$PWD/include/helper/ -lhelper

INCLUDEPATH += $$PWD/include/helper
DEPENDPATH += $$PWD/include/helper
