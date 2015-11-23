#-------------------------------------------------
#
# Project created by QtCreator 2015-11-20T11:19:48
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/textures
TARGET = textures
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    window.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    window.h \
    glwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    textures.qrc
