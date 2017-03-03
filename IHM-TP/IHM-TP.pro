#HANSER Florian
#BAUER Gauillaume

#-------------------------------------------------
#
# Project created by QtCreator 2017-03-01T18:03:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHM-TP
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    blackbox.cpp \
    interface.cpp \
    simulation.cpp \
    simulationwindow.cpp \
    valve.cpp \
    sluicecomponent.cpp \
    gate.cpp \
    light.cpp

HEADERS  += blackbox.h \
    enums.h \
    interface.h \
    simulation.h \
    simulationwindow.h \
    sluicecomponent.h \
    valve.h \
    gate.h \
    light.h
    enums.h

FORMS    += interface.ui
