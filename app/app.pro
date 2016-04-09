TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/serial.cpp \
    src/rs232.c

HEADERS += \
    include/serial.h \
    include/rs232.h \
    include/plot.h \
    include/elements.h \
    include/buffer.h
