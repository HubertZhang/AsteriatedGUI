#-------------------------------------------------
#
# Project created by QtCreator 2013-11-28T23:40:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = textserver
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    agserver.cpp

HEADERS  += dialog.h \
    agserver.h

FORMS    += dialog.ui
