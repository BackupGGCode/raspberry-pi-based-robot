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
LIBS += -LD:/3rdParty/opencv-2.4.7/lib \
    opencv_core248.lib \
    opencv_highgui248.lib \
    opencv_imgproc248.lib \
    opencv_video248.lib \
    opencv_objdetect248.lib \
    opencv_ml248.lib \
    opencv_features2d248.lib \
    opencv_calib3d248.lib \
    opencv_legacy248.lib
}
release {
message(Debug build)
LIBS += -LD:/3rdParty/opencv-2.4.7/lib \
    opencv_core248d.lib \
    opencv_highgui248d.lib \
    opencv_imgproc248d.lib \
    opencv_video248d.lib \
    opencv_objdetect248d.lib \
    opencv_ml248d.lib \
    opencv_features2d248d.lib \
    opencv_calib3d248d.lib \
    opencv_legacy248d.lib
}




SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
