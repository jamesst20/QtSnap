#-------------------------------------------------
#
# Project created by QtCreator 2014-12-19T10:06:00
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = QtSnap-Library
TEMPLATE = lib
CONFIG += staticlib

SOURCES += Snapchat.cpp

HEADERS += Snapchat.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
