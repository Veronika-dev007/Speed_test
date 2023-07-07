#-------------------------------------------------
#
# Project created by QtCreator 2023-07-03T16:14:57
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = udpReceiver
TEMPLATE = app


SOURCES += main.cpp\
        receiver.cpp

HEADERS  += receiver.h

FORMS    += receiver.ui
