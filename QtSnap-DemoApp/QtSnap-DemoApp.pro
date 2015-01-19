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

INCLUDEPATH += $$PWD/../QtSnap-Library
DEPENDPATH += $$PWD/../QtSnap-Library

unix|win32: LIBS += -L$$OUT_PWD/../QtSnap-Library/ -lQtSnap-Library

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../QtSnap-Library/QtSnap-Library.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../QtSnap-Library/libQtSnap-Library.a
