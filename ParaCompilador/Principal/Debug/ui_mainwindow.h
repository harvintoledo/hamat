/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Abrir_Proyecto;
    QAction *action_Cerrar_Proyecto;
    QAction *action_Guardar_Proyecto;
    QAction *actionGuardar_Como;
    QAction *action_Rehacer;
    QAction *action_Deshacer;
    QAction *action_Copiar;
    QAction *action_Cortar;
    QAction *action_Pegar;
    QAction *action_Sobre_aplicacion;
    QAction *action_Guia_de_Usuario;
    QAction *action_Nuevo;
    QAction *action_Generar_Plantilla;
    QWidget *centralWidget;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menu_Nuevo;
    QMenu *menuEdicion;
    QMenu *menuAyuda;
    QMenu *menuPlantillla;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setMaximumSize(QSize(800, 600));
        MainWindow->setStyleSheet(QStringLiteral(""));
        action_Abrir_Proyecto = new QAction(MainWindow);
        action_Abrir_Proyecto->setObjectName(QStringLiteral("action_Abrir_Proyecto"));
        action_Cerrar_Proyecto = new QAction(MainWindow);
        action_Cerrar_Proyecto->setObjectName(QStringLiteral("action_Cerrar_Proyecto"));
        action_Guardar_Proyecto = new QAction(MainWindow);
        action_Guardar_Proyecto->setObjectName(QStringLiteral("action_Guardar_Proyecto"));
        actionGuardar_Como = new QAction(MainWindow);
        actionGuardar_Como->setObjectName(QStringLiteral("actionGuardar_Como"));
        action_Rehacer = new QAction(MainWindow);
        action_Rehacer->setObjectName(QStringLiteral("action_Rehacer"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Redo"), QSize(), QIcon::Normal, QIcon::Off);
        action_Rehacer->setIcon(icon);
        action_Deshacer = new QAction(MainWindow);
        action_Deshacer->setObjectName(QStringLiteral("action_Deshacer"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Undo"), QSize(), QIcon::Normal, QIcon::Off);
        action_Deshacer->setIcon(icon1);
        action_Copiar = new QAction(MainWindow);
        action_Copiar->setObjectName(QStringLiteral("action_Copiar"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Images/Copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Copiar->setIcon(icon2);
        action_Cortar = new QAction(MainWindow);
        action_Cortar->setObjectName(QStringLiteral("action_Cortar"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Images/Cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Cortar->setIcon(icon3);
        action_Pegar = new QAction(MainWindow);
        action_Pegar->setObjectName(QStringLiteral("action_Pegar"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Images/Paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Pegar->setIcon(icon4);
        action_Sobre_aplicacion = new QAction(MainWindow);
        action_Sobre_aplicacion->setObjectName(QStringLiteral("action_Sobre_aplicacion"));
        action_Guia_de_Usuario = new QAction(MainWindow);
        action_Guia_de_Usuario->setObjectName(QStringLiteral("action_Guia_de_Usuario"));
        action_Nuevo = new QAction(MainWindow);
        action_Nuevo->setObjectName(QStringLiteral("action_Nuevo"));
        action_Generar_Plantilla = new QAction(MainWindow);
        action_Generar_Plantilla->setObjectName(QStringLiteral("action_Generar_Plantilla"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 50, 781, 491));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        font.setPointSize(12);
        textEdit->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menu_Nuevo = new QMenu(menuBar);
        menu_Nuevo->setObjectName(QStringLiteral("menu_Nuevo"));
        menuEdicion = new QMenu(menuBar);
        menuEdicion->setObjectName(QStringLiteral("menuEdicion"));
        menuAyuda = new QMenu(menuBar);
        menuAyuda->setObjectName(QStringLiteral("menuAyuda"));
        menuPlantillla = new QMenu(menuBar);
        menuPlantillla->setObjectName(QStringLiteral("menuPlantillla"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_Nuevo->menuAction());
        menuBar->addAction(menuEdicion->menuAction());
        menuBar->addAction(menuPlantillla->menuAction());
        menuBar->addAction(menuAyuda->menuAction());
        menu_Nuevo->addAction(action_Nuevo);
        menu_Nuevo->addSeparator();
        menu_Nuevo->addAction(action_Abrir_Proyecto);
        menu_Nuevo->addSeparator();
        menu_Nuevo->addAction(action_Cerrar_Proyecto);
        menu_Nuevo->addSeparator();
        menu_Nuevo->addAction(action_Guardar_Proyecto);
        menu_Nuevo->addAction(actionGuardar_Como);
        menuEdicion->addAction(action_Rehacer);
        menuEdicion->addAction(action_Deshacer);
        menuEdicion->addSeparator();
        menuEdicion->addAction(action_Copiar);
        menuEdicion->addAction(action_Cortar);
        menuEdicion->addAction(action_Pegar);
        menuAyuda->addAction(action_Sobre_aplicacion);
        menuAyuda->addAction(action_Guia_de_Usuario);
        menuPlantillla->addAction(action_Generar_Plantilla);
        mainToolBar->addAction(action_Rehacer);
        mainToolBar->addAction(action_Deshacer);
        mainToolBar->addAction(action_Copiar);
        mainToolBar->addAction(action_Cortar);
        mainToolBar->addAction(action_Pegar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "OCCAM - Arquitectura de Maquinas", 0));
        action_Abrir_Proyecto->setText(QApplication::translate("MainWindow", "&Abrir Proyecto", 0));
        action_Cerrar_Proyecto->setText(QApplication::translate("MainWindow", "&Cerrar Proyecto", 0));
        action_Guardar_Proyecto->setText(QApplication::translate("MainWindow", "&Guardar Proyecto", 0));
        actionGuardar_Como->setText(QApplication::translate("MainWindow", "Guardar &Como", 0));
        action_Rehacer->setText(QApplication::translate("MainWindow", "&Rehacer", 0));
        action_Rehacer->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", 0));
        action_Deshacer->setText(QApplication::translate("MainWindow", "&Deshacer", 0));
        action_Deshacer->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0));
        action_Copiar->setText(QApplication::translate("MainWindow", "&Copiar", 0));
        action_Copiar->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0));
        action_Cortar->setText(QApplication::translate("MainWindow", "&Cortar", 0));
        action_Cortar->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0));
        action_Pegar->setText(QApplication::translate("MainWindow", "&Pegar", 0));
        action_Pegar->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", 0));
        action_Sobre_aplicacion->setText(QApplication::translate("MainWindow", "&Sobre  aplicacion", 0));
        action_Guia_de_Usuario->setText(QApplication::translate("MainWindow", "&Guia de Usuario", 0));
        action_Nuevo->setText(QApplication::translate("MainWindow", "&Nuevo", 0));
        action_Generar_Plantilla->setText(QApplication::translate("MainWindow", "&Generar Plantilla", 0));
        menu_Nuevo->setTitle(QApplication::translate("MainWindow", "&Archivo", 0));
        menuEdicion->setTitle(QApplication::translate("MainWindow", "Edicion", 0));
        menuAyuda->setTitle(QApplication::translate("MainWindow", "Ayuda", 0));
        menuPlantillla->setTitle(QApplication::translate("MainWindow", "Plantillla", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
