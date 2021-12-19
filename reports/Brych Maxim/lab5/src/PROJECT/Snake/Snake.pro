QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS
LIBS += -L./-lHelper
LIBS += -L./-lAbout
LIBS += -L./release -llevel1
LIBS += -L./release/level -llevel2
LIBS += -L./release/level -llevel3
LIBS += -L./release/level -llevel4
LIBS += -L./release/level -llevel5
LIBS += -L./release/level -llevel6
LIBS += -L./release/level -llevel7
LIBS += -L./release/level -llevel8
LIBS += -L./release/level -llevel9
LIBS += -L./release/level -llevel10
LIBS += -L./release/level -llevel11
LIBS += -L./release/level -llevel12
LIBS += -L./release/level -llevel13
LIBS += -L./release/level -llevel14
LIBS += -L./release/level -llevel15
LIBS += -L./release/level -llevel16
LIBS += -L./release/level -llevel17
LIBS += -L./release/level -llevel18
LIBS += -L./release/level -llevel19
LIBS += -L./release/level -llevel20
LIBS += -L./release/level -llevel21
LIBS += -L./release/level -llevel22
LIBS += -L./release/level -llevel23
LIBS += -L./release/level -llevel24
LIBS += -L./release/level -llevel25
LIBS += -L./release/level -llevel26
LIBS += -L./release/level -llevel27
LIBS += -L./release/level -llevel28
LIBS += -L./release/level -llevel29
LIBS += -L./release/level -llevel30
LIBS += -L./release/level -llevel31
LIBS += -L./release/level -llevel32
LIBS += -L./release/level -llevel33
LIBS += -L./release/level -llevel34
LIBS += -L./release/level -llevel35
LIBS += -L./release/level -llevel36
LIBS += -L./release/level -llevel37
LIBS += -L./release/level -llevel38
LIBS += -L./release/level -llevel39
LIBS += -L./release/level -llevel40
LIBS += -L./release/level -llevel41
LIBS += -L./release/level -llevel42
LIBS += -L./release/level -llevel43
LIBS += -L./release/level -llevel44
LIBS += -L./release/level -llevel45
LIBS += -L./release/level -llevel46
LIBS += -L./release/level -llevel47
LIBS += -L./release/level -llevel48
LIBS += -L./release/level -llevel49
LIBS += -L./release/level -llevel50

INCLUDEPATH += ../interfaces

SOURCES += \
    game.cpp \
    main.cpp \
    menu.cpp \
    snake.cpp \
    thread.cpp

HEADERS += \
    about.h \
    about_global.h \
    helper.h \
    helper_global.h \
    snake.h \
    thread.h

FORMS += \
    snake.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
