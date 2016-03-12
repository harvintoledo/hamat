#-------------------------------------------------
#
# Project created by QtCreator 2015-11-23T09:11:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += opengl
TARGET = 2dpainting
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    helper.cpp \
    glwidget.cpp \
    widget.cpp \
    window.cpp

HEADERS  += mainwindow.h \
    helper.h \
    glwidget.h \
    widget.h \
    window.h

FORMS    += mainwindow.ui
