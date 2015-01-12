#-------------------------------------------------
#
# Project created by QtCreator 2014-11-15T18:00:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Convolutional_net
TEMPLATE = app

unix{
    CONFIG += link_pkgconfig
    PKGCONFIG +=opencv
}
win32{
    INCLUDEPATH += C:\opencv246bin\install\include \
                   C:\opencv246bin\install\include\opencv \
                   C:\opencv246bin\install\include\opencv2

    LIBS += -LC:\\opencv246bin\\install\\lib \
            -lopencv_core246.dll \
            -lopencv_highgui246.dll \
            -lopencv_imgproc246.dll \
            -lopencv_features2d246.dll \
            -lopencv_calib3d246.dll \
            -lopencv_video246.dll \
            -lopencv_videostab246.dll

}


SOURCES += main.cpp\
        convolutional.cpp

HEADERS  += convolutional.h

FORMS    += convolutional.ui
