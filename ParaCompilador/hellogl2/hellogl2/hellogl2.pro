#-------------------------------------------------
#
# Project created by QtCreator 2015-11-23T10:04:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += opengl
TARGET = hellogl2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    logo.cpp \
    window.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    logo.h \
    window.h
