#-------------------------------------------------
#
# Project created by QtCreator 2015-07-02T09:28:45
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = tcpccc
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp

HEADERS += \
    server.h

QT += network

QT += widgets
