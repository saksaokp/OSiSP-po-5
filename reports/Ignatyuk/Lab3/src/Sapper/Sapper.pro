QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = sapper
TEMPLATE = app

CONFIG += c++17

SOURCES += \
        main.cpp \
        sapper.cpp

HEADERS += \
        About_global.hpp \
        HelperClass_global.hpp \
        about.hpp \
        helperclass.hpp \
        sapper.hpp

RESOURCES += \
    icons.qrc

LIBS += "./helper_class.dll"
LIBS += "./about.dll"
