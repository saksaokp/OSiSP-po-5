
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS +=./release/Helper.dll
LIBS +=./release/About.dll
LIBS +=./release/Font.dll
TARGET = xonix
TEMPLATE = app


SOURCES += qt/main.cpp    \
           qt/widget.cpp  \
           qt/game.cpp    \
           engine/xonix.c \
           qt/gitem.cpp

HEADERS  += qt/widget.h   \
    about.h \
    about_global.h \
    font.h \
    font_global.h \
    helper.h \
    helper_global.h \
    qt/game.h             \
    engine/xonix.h        \
    qt/gitem.h

FORMS    += qt/widget.ui
