#-------------------------------------------------
#
# Project created by QtCreator 2013-07-14T16:24:00
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = Robot
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Communication/UART/SerialCommunication.cpp \
    Communication/TCP/TcpServer.cpp \
    Communication/ComManager/Commanager.cpp \
    Robot.cpp

HEADERS += \
    Communication/UART/SerialCommunication.h \
    Communication/TCP/TcpServer.h \
    Communication/ComManager/Commanager.h \
    Robot.h
