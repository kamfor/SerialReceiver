QT += widgets serialport
QT += widgets printsupport

TARGET = terminal
TEMPLATE = app

SOURCES += \
    main.cpp \
    src/mainwindow.cpp \
    src/settingsdialog.cpp \
    src/console.cpp \
    plots/qcustomplot.cpp

HEADERS += \
    include/mainwindow.h \
    include/settingsdialog.h \
    include/console.h \
    plots/qcustomplot.h

FORMS += \
    forms/mainwindow.ui \
    forms/settingsdialog.ui \
    forms/plot.ui

RESOURCES +=
