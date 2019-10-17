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
    AntenaImage.cpp \
    room.cpp \
    MainWindow.cpp \
    help.cpp \
    antena.cpp \
    settings.cpp \
    ray.cpp \
    qcustomplot.cpp \
    plots.cpp \
    Line.cpp \
    Wall.cpp \
    DiffractionPoints.cpp \
    Building.cpp \
    Model.cpp \
    GraphicsBuilding.cpp

HEADERS  += \
    AntenaImage.h \
    room.h \
    MainWindow.h \
    help.h \
    antena.h \
    settings.h \
    ray.h \
    qcustomplot.h \
    plots.h \
    Line.h \
    Wall.h \
    DiffractionPoints.h \
    Building.h \
    Model.h \
    Visualizer.h \
    GraphicsBuilding.h \
    MovableObject.h
RESOURCES = icon.qrc

FORMS    += ieee80211g.ui \     #Qt design template
    help.ui \
    settings.ui \
    plots.ui
