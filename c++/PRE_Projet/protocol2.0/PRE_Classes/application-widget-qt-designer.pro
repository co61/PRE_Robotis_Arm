#-------------------------------------------------
#
# Project created by QtCreator 2016-11-13T18:25:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PRE_Pattern
TEMPLATE = app

INCLUDEPATH += ../../../include/ ../../../include/dynamixel_sdk /usr/include/qwt /usr/include/opencv4


LIBS  += ../lib/x64/libLeap.so -Wl,-rpath,../lib/x64
LIBS  += -lboost_system -lboost_filesystem
LIBS  += -ldxl_x64_cpp
LIBS  += -lrt -lqwt-qt5 -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio


SOURCES += PRE_Manette.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
