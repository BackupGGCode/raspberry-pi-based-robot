#-------------------------------------------------
#
# Project created by QtCreator 2014-10-25T20:05:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = example
TEMPLATE = app

INCLUDEPATH += D:/3rdParty/opencv-2.4.7/include

#Itt mindíg az opencv verziójának megfelelően változik a lib neve:
#Pl. A 2.4.0-ás opencv-ben: libopencv_core240, míg a
# 2.4.8-as opencv-ben, már: libopencv_core248 a lib neve.

debug {
message(Release build)
LIBS += -LD:/3rdParty/opencv-2.4.10/vc11x86/lib \
    opencv_core2410.lib \
    opencv_highgui2410.lib \
    opencv_imgproc2410.lib \
    opencv_video2410.lib \
    opencv_objdetect2410.lib \
    opencv_ml2410.lib \
    opencv_features2d2410.lib \
    opencv_calib3d2410.lib \
    opencv_legacy2410.lib
}
release {
message(Debug build)
LIBS += -LD:/3rdParty/opencv-2.4.7/vc11x86/lib \
    opencv_core2410d.lib \
    opencv_highgui2410d.lib \
    opencv_imgproc2410d.lib \
    opencv_video2410d.lib \
    opencv_objdetect2410d.lib \
    opencv_ml2410d.lib \
    opencv_features2d2410d.lib \
    opencv_calib3d2410d.lib \
    opencv_legacy2410d.lib
}


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
