#-------------------------------------------------
#
# Project created by QtCreator 2014-12-19T10:07:39
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = QtSnap-DemoApp
CONFIG   += console
CONFIG   -= app_bundle

CONFIG += c++11
CONFIG += c++14


TEMPLATE = app


SOURCES += main.cpp

win32: LIBS += -L$$PWD/../build-QtSnap-Library-Desktop_Qt_5_4_0_MinGW_32bit-Debug/debug/ -lQtSnap-Library
macx: LIBS += -L$$PWD/../build-QtSnap-Library-Desktop_Qt_5_4_0_clang_64bit-Debug/ -lQtSnap-Library

INCLUDEPATH += $$PWD/../QtSnap-Library
DEPENDPATH += $$PWD/../QtSnap-Library
