#-------------------------------------------------
#
# Project created by QtCreator 2014-08-13T11:03:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proyectoOrga
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialognuevo.cpp \
    campo.cpp \
    header.cpp

HEADERS  += mainwindow.h \
    dialognuevo.h \
    campo.h \
    header.h

FORMS    += mainwindow.ui \
    dialognuevo.ui
CONFIG += c++11
