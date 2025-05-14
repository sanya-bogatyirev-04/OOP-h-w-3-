TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        database.cpp \
        main.cpp \
        menu.cpp \
        modem.cpp

HEADERS += \
    colors.h \
    database.h \
    menu.h \
    modem.h

DISTFILES += \
    modem
