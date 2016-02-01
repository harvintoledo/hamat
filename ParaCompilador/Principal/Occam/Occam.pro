#-------------------------------------------------
#
# Project created by QtCreator 2016-01-31T11:31:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Occam
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    classwizard.cpp \
    intropage.cpp \
    classinfopage.cpp \
    codestylepage.cpp \
    conclusionpage.cpp \
    outputfilespage.cpp

HEADERS  += mainwindow.h \
    classwizard.h \
    intropage.h \
    classinfopage.h \
    codestylepage.h \
    conclusionpage.h \
    outputfilespage.h

FORMS    += mainwindow.ui
