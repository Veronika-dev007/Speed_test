#-------------------------------------------------
#
# Project created by QtCreator 2023-07-03T15:34:26
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = udpSender
TEMPLATE = app


SOURCES += main.cpp \
    sender.cpp

HEADERS  += \
    sender.h

FORMS    += widget.ui
