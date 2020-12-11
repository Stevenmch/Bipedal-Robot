QT += core
QT -= gui

TARGET = DetectorDeObjetos
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

//librerias
INCLUDEPATH += /usr/include/opencv
INCLUDEPATH += /usr/include/opencv2
LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc
