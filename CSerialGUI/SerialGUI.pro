#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T22:39:20
#
#-------------------------------------------------

QT       += core gui
CONFIG   += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    ../app/src/buffer.cpp \
    ../app/src/handlefile.cpp \
    ../app/src/interface.cpp \
    ../app/src/serial.cpp \
    ../app/src/rs232.c \
    console.cpp

HEADERS  += mainwindow.h \
    settings.h \
    ../app/include/buffer.h \
    ../app/include/handlefile.h \
    ../app/include/interface.h \
    ../app/include/plot.h \
    ../app/include/rs232.h \
    ../app/include/serial.h \
    console.h

FORMS    += mainwindow.ui \
    settings.ui
