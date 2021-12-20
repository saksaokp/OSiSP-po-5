QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = sapper
TEMPLATE = app

CONFIG += c++17

SOURCES += \
        main.cpp \
        push_button.cpp \
        sapper.cpp

HEADERS += \
        push_button.hpp \
        sapper.hpp

RESOURCES += \
    icons.qrc
