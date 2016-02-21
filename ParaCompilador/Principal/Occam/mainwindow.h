#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include "classwizard.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_Copiar_triggered();

    void on_action_Nuevo_triggered();

    void on_action_Cortar_triggered();

    void on_action_Pegar_triggered();

    void on_action_Rehacer_triggered();

    void on_action_Deshacer_triggered();

    void on_action_Abrir_Proyecto_triggered();

    void on_action_Guardar_Proyecto_triggered();

    void on_actionGuardar_Como_triggered();

private:
    Ui::MainWindow *ui;
protected:
    QString slRutaDeTrabajo;
    ClassWizard omWizard;
};

#endif // MAINWINDOW_H
