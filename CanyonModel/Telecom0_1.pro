#-------------------------------------------------
#-------------------------------------------------
#
# Project created by QtCreator 2018-04-02T19:41:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets  printsupport # Simple version checking for portability

CONFIG += c++11
TARGET = Telecom0_1
TEMPLATE = app

SOURCES += main.cpp\
    room.cpp \
    MainWindow.cpp \
    help.cpp \
    antena.cpp \
    wall.cpp \
    settings.cpp \
    ray.cpp \
    lineo.cpp \
    qcustomplot.cpp \
    plots.cpp

HEADERS  += \
    room.h \
    MainWindow.h \
    help.h \
    antena.h \
    wall.h \
    settings.h \
    ray.h \
    lineo.h \
    qcustomplot.h \
    plots.h
RESOURCES = icon.qrc

FORMS    += ieee80211g.ui \     #Qt design template
    help.ui \
    settings.ui \
    plots.ui
