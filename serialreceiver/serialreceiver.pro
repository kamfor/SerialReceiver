QT += widgets serialport
QT += widgets printsupport
QT += serialport

TARGET = serialreceiver
TEMPLATE = app

SOURCES += \
    main.cpp \
    src/mainwindow.cpp \
    src/settingsdialog.cpp \
    src/console.cpp \
    plots/qcustomplot.cpp \
    src/readthread.cpp

HEADERS += \
    include/mainwindow.h \
    include/settingsdialog.h \
    include/console.h \
    plots/qcustomplot.h \
    include/readthread.h

FORMS += \
    forms/mainwindow.ui \
    forms/settingsdialog.ui

