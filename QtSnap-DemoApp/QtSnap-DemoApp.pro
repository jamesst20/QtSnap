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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-QtSnap-Library-Desktop_Qt_5_4_0_MinGW_32bit-Debug/release/ -lQtSnap-Library
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-QtSnap-Library-Desktop_Qt_5_4_0_MinGW_32bit-Debug/debug/ -lQtSnap-Library

INCLUDEPATH += $$PWD/../QtSnap-Library
DEPENDPATH += $$PWD/../QtSnap-Library

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-QtSnap-Library-Desktop_Qt_5_4_0_MinGW_32bit-Debug/release/libQtSnap-Library.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-QtSnap-Library-Desktop_Qt_5_4_0_MinGW_32bit-Debug/debug/libQtSnap-Library.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-QtSnap-Library-Desktop_Qt_5_4_0_MinGW_32bit-Debug/release/QtSnap-Library.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-QtSnap-Library-Desktop_Qt_5_4_0_MinGW_32bit-Debug/debug/QtSnap-Library.lib
