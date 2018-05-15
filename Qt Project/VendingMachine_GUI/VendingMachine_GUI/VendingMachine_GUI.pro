TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    events.cpp \
    hal.cpp

HEADERS += \
    events.h \
    hal.h \
    states.h
