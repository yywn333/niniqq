#-------------------------------------------------
#
# Project created by QtCreator 2015-07-02T09:02:12
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = tcptest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    client.cpp

QT += network

HEADERS += \
    client.h

QT += network
QT += widgets
