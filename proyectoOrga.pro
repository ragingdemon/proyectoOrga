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
    header.cpp \
    dialogver.cpp \
    dialogagregar.cpp \
    indicel.cpp \
    llave.cpp \
    arbolb.cpp \
    dialogbuscar.cpp \
    dialogcruce.cpp

HEADERS  += mainwindow.h \
    dialognuevo.h \
    campo.h \
    header.h \
    dialogver.h \
    dialogagregar.h \
    indicel.h \
    llave.h \
    arbolb.h \
    dialogbuscar.h \
    dialogcruce.h

FORMS    += mainwindow.ui \
    dialognuevo.ui \
    dialogver.ui \
    dialogagregar.ui \
    dialogbuscar.ui \
    dialogcruce.ui
CONFIG += c++11
