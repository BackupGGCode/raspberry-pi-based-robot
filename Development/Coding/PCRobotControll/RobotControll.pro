#-------------------------------------------------
#
# Project created by QtCreator 2013-08-14T10:29:03
#
#-------------------------------------------------

QT       += core gui opengl network

TARGET = RobotControll
TEMPLATE = app


SOURCES += main.cpp\
        controllpanel.cpp \
    Displays/displaymanager.cpp \
    Displays/cameradisplay.cpp \
    Displays/myglwidget.cpp \
    Displays/qcustomplot.cpp \
    SensorData/sensorsdataformat.cpp \
    Communication/TcpClient.cpp \
    Communication/TcpServer.cpp \
    RemoteControll/ManualControll/manualcontroll.cpp \
    RemoteControll/AutoPilot/autopilot.cpp

HEADERS  += controllpanel.h \
    Displays/displaymanager.h \
    Displays/cameradisplay.h \
    Displays/myglwidget.h \
    Displays/qcustomplot.h \
    SensorData/sensorsdataformat.h \
    Communication/TcpClient.h \
    Communication/TcpServer.h \
    RemoteControll/ManualControll/manualcontroll.h \
    RemoteControll/AutoPilot/autopilot.h

FORMS    += controllpanel.ui \
    Displays/displaymanager.ui \
    Displays/cameradisplay.ui \
    RemoteControll/ManualControll/manualcontroll.ui \
    RemoteControll/AutoPilot/autopilot.ui
