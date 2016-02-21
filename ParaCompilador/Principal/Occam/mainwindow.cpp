#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setCentralWidget(this->ui->textEdit);
}
MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::on_action_Copiar_triggered() {
    ui->textEdit->copy();
}
void MainWindow::on_action_Nuevo_triggered() {
    omWizard.show();

    slRutaDeTrabajo = omWizard.getUbicacionDelProyecto() + "/" + omWizard.getNombreDelProyecto() + ".occam";
    QString slRutaIndicadaPorUsuario = slRutaDeTrabajo;
    if(!slRutaIndicadaPorUsuario.isEmpty()) {
        QFile olArchivoALeerEnEditorDeTexto(slRutaIndicadaPorUsuario);
        if(olArchivoALeerEnEditorDeTexto.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream olTextStreamArchivoLeido(&olArchivoALeerEnEditorDeTexto);
            QString text = olTextStreamArchivoLeido.readAll();
            olArchivoALeerEnEditorDeTexto.close();
            ui->textEdit->setPlainText(text);
        }
    }

}
void MainWindow::on_action_Cortar_triggered() {
    ui->textEdit->cut();
}
void MainWindow::on_action_Pegar_triggered() {
    ui->textEdit->paste();
}
void MainWindow::on_action_Rehacer_triggered() {
    ui->textEdit->redo();
}
void MainWindow::on_action_Deshacer_triggered() {
    ui->textEdit->undo();
}
void MainWindow::on_action_Abrir_Proyecto_triggered() {
    QString slRutaIndicadaPorUsuario = QFileDialog::getOpenFileName(this, "Abrir proyecto Occam");
    if(!slRutaIndicadaPorUsuario.isEmpty()) {
        QFile olArchivoALeerEnEditorDeTexto(slRutaIndicadaPorUsuario);
        if(olArchivoALeerEnEditorDeTexto.open(QFile::ReadOnly | QFile::Text)) {
            slRutaDeTrabajo = slRutaIndicadaPorUsuario;
            QTextStream n(&olArchivoALeerEnEditorDeTexto);
            QString text = n.readAll();
            olArchivoALeerEnEditorDeTexto.close();
            ui->textEdit->setPlainText(text);
        }
    }
}
void MainWindow::on_action_Guardar_Proyecto_triggered() {
    QFile olArchivoAGuardarDesdeEditorTexto(slRutaDeTrabajo);
    if(olArchivoAGuardarDesdeEditorTexto.open(QFile::ReadWrite | QFile::Text )) {
        QTextStream stream(&olArchivoAGuardarDesdeEditorTexto);
        stream << ui->textEdit->toPlainText();
        olArchivoAGuardarDesdeEditorTexto.flush();
        olArchivoAGuardarDesdeEditorTexto.close();
    }
}
void MainWindow::on_actionGuardar_Como_triggered() {
    QString slRutaArhivoIndicadaPorUsuario = QFileDialog::getSaveFileName(this, "Guardar como");
    if(!slRutaArhivoIndicadaPorUsuario.isEmpty()) {
        slRutaDeTrabajo = slRutaArhivoIndicadaPorUsuario;
        on_action_Guardar_Proyecto_triggered();
    }
}
