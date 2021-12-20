QT += core gui widgets network

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

LIBS += "C:/Users/User/Desktop/OS/lab_4/build-Sapper-Desktop_Qt_6_1_2_MinGW_64_bit-Debug/debug/helper_class.dll"
LIBS += "C:/Users/User/Desktop/OS/lab_4/build-Sapper-Desktop_Qt_6_1_2_MinGW_64_bit-Debug/debug/about.dll"
