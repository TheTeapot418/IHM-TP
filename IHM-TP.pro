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
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += . \
    headers \
    forms \
    resources

SOURCES += sources/main.cpp\
    sources/blackbox.cpp \
    sources/interface.cpp \
    sources/simulation.cpp \
    sources/simulationwindow.cpp \
    sources/valve.cpp \
    sources/gate.cpp \
    sources/light.cpp \
    sources/background.cpp \
    sources/water.cpp \
    sources/sluicecomponent.cpp

HEADERS  += headers/blackbox.h \
    headers/enums.h \
    headers/interface.h \
    headers/simulation.h \
    headers/simulationwindow.h \
    headers/sluicecomponent.h \
    headers/valve.h \
    headers/gate.h \
    headers/light.h \
    headers/paintable.h \
    headers/background.h \
    headers/water.h
    headers/enums.h

FORMS    += forms/interface.ui

RESOURCES += resources/simulation-assets.qrc
