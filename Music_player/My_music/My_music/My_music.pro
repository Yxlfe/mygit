#-------------------------------------------------
#
# Project created by QtCreator 2019-07-30T17:29:28
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = My_music
TEMPLATE = app


SOURCES += main.cpp\
        main_widget.cpp \
    sendinfo.cpp \
    recvinfo.cpp

HEADERS  += main_widget.h \
    sendinfo.h \
    recvinfo.h

FORMS    += main_widget.ui

RESOURCES += \
    image.qrc

RC_ICONS = music.ico

