QMAKE_LFLAGS_RELEASE += -static -static-libgcc
RC_FILE = myapp.rc
QT += core
QT -= gui

CONFIG += c++11

TARGET = predator-prey
CONFIG -= app_bundle
QT += widgets

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    mwindow.h \
    advanced_settings.h
