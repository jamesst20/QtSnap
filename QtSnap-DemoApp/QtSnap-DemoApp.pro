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
CONFIG += c++14

TEMPLATE = app


SOURCES += main.cpp

win32: LIBS += -L$$PWD/../build-QtSnap-Library-Desktop_Qt_5_4_0_MinGW_32bit-Debug/debug/ -lQtSnap-Library

INCLUDEPATH += $$PWD/../QtSnap-Library
DEPENDPATH += $$PWD/../QtSnap-Library

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../build-QtSnap-Library-Desktop_Qt_5_4_0_MinGW_32bit-Debug/debug/QtSnap-Library.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../build-QtSnap-Library-Desktop_Qt_5_4_0_MinGW_32bit-Debug/debug/libQtSnap-Library.a

win32: LIBS += -L$$PWD/../libs/QCA/bin/ -llibqca

INCLUDEPATH += $$PWD/../libs/QCA/includes
DEPENDPATH += $$PWD/../libs/QCA/includes
