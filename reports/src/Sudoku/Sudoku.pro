#-------------------------------------------------
#
# Project created by QtCreator 2021-10-02T16:55:24
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = Sudoku
TEMPLATE = app

SOURCES += main.cpp\
        Sudoku.cpp \
    Board.cpp \
    Cell.cpp \
    Position.cpp \
    DefaultBoards.cpp

HEADERS  += Sudoku.h \
    Board.h \
    Cell.h \
    Position.h \
    DefaultBoards.h

FORMS    += Sudoku.ui \
    Board.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Sudoku.qrc



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-fontPluginInterface-Desktop_Qt_6_2_1_MinGW_64_bit-Debug/release/ -lfontPluginInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-fontPluginInterface-Desktop_Qt_6_2_1_MinGW_64_bit-Debug/debug/ -lfontPluginInterface
else:unix: LIBS += -L$$PWD/../build-fontPluginInterface-Desktop_Qt_6_2_1_MinGW_64_bit-Debug/ -lfontPluginInterface
INCLUDEPATH += $$PWD/../pluginInterface
DEPENDPATH += $$PWD/../pluginInterface
