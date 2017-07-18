#-------------------------------------------------
#
# Project created by QtCreator 2017-07-14T14:41:44
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chat-client
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

RESOURCES += \
    myicon.qrc
