#-------------------------------------------------
#-------------------------------------------------
#
# Project created by QtCreator 2018-04-02T19:41:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets   # Simple version checking for portability

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
    coverage.cpp

HEADERS  += \
    room.h \
    MainWindow.h \
    help.h \
    antena.h \
    wall.h \
    settings.h \
    ray.h \
    lineo.h \
    coverage.h

FORMS    += ieee80211g.ui \     #Qt design template
    help.ui \
    settings.ui
