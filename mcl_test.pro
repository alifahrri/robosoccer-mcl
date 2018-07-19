#-------------------------------------------------
#
# Project created by QtCreator 2017-06-08T21:06:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets gamepad

TARGET = mcl_test
TEMPLATE = app

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += gui
INCLUDEPATH += include

SOURCES += main.cpp\
        gui/mainwindow.cpp \
    gui/field.cpp \
    gui/controldialog.cpp \
    gui/robot.cpp \
    gui/whitepoints.cpp \
    src/mcl.cpp \
    gui/mclitem.cpp \
    gui/mcldialog.cpp \
    gui/sensorview.cpp \
    gui/distancematrix.cpp

HEADERS  += gui/mainwindow.h \
    gui/field.h \
    gui/controldialog.h \
    gui/robot.h \
    gui/whitepoints.h \
    include/mcl.h \
    gui/mclitem.h \
    gui/mcldialog.h \
    gui/sensorview.h \
    gui/distancematrix.h \
    include/util.hpp

FORMS    += gui/mainwindow.ui \
    gui/controldialog.ui \
    gui/mcldialog.ui \
    gui/sensorview.ui \
    gui/distancematrix.ui

RESOURCES += \
    res/resource.qrc
