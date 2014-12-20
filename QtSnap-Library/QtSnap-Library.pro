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
CONFIG += c++14

SOURCES += Snapchat.cpp \
    NetworkRequestMaker.cpp \
    TokenLib.cpp \
    Utils.cpp

HEADERS += Snapchat.h \
    NetworkRequestMaker.h \
    TokenLib.h \
    Utils.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
