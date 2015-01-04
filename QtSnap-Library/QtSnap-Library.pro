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

CONFIG += c++11
CONFIG += c++14


SOURCES += Snapchat.cpp \
    NetworkRequestMaker.cpp \
    TokenLib.cpp \
    Utils.cpp \
    Friend.cpp \
    FriendController.cpp \
    StoryController.cpp \
    Story.cpp \
    Viewer.cpp \
    Snap.cpp \
    ConversationController.cpp \
    Encryption.cpp \
    Crypto/aes.cpp

HEADERS += Snapchat.h \
    NetworkRequestMaker.h \
    TokenLib.h \
    Utils.h \
    Friend.h \
    FriendController.h \
    StoryController.h \
    Story.h \
    Viewer.h \
    Snap.h \
    ConversationController.h \
    Encryption.h \
    Crypto/aes.h
