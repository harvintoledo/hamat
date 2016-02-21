#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setCentralWidget(this->ui->textEdit);
    // pomWizard = new ClassWizard;
    //    pomWizard->setParent(this);
    bmPlantillaOcamAbierta = false;
    bmPlantillaCompilada  = true;
    smRutaDeTrabajo =
    smRutaNombreArchivoDeTrabajo =
    smNombreArchivoDeTrabajo = "";

}
MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::on_action_Copiar_triggered() {
    ui->textEdit->copy();
}
void MainWindow::AcceptWizardPage() {
    smRutaDeTrabajo = pomWizard->getUbicacionDelProyecto();
    smNombreArchivoDeTrabajo = pomWizard->getNombreDelProyecto();
    smRutaNombreArchivoDeTrabajo = smRutaDeTrabajo + "\\" + smNombreArchivoDeTrabajo + ".occam";
    if(!smRutaNombreArchivoDeTrabajo.isEmpty()) {
        QFile olArchivoALeerEnEditorDeTexto(smRutaNombreArchivoDeTrabajo);
        if(olArchivoALeerEnEditorDeTexto.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream olTextStreamArchivoLeido(&olArchivoALeerEnEditorDeTexto);
            QString text = olTextStreamArchivoLeido.readAll();
            olArchivoALeerEnEditorDeTexto.close();
            ui->textEdit->setPlainText(text);
            bmPlantillaOcamAbierta = true;
        }
    }
    pomWizard->close();
    disconnect(pomWizard, SIGNAL(accepted()), this, SLOT(AcceptWizardPage()));
    delete pomWizard;
}
void MainWindow::on_action_Nuevo_triggered() {
    pomWizard = new ClassWizard;
    pomWizard->show();
    connect(pomWizard, SIGNAL(accepted()), this, SLOT(AcceptWizardPage()));
    //    smRutaDeTrabajo = pomWizard->getUbicacionDelProyecto() + "/" + pomWizard->getNombreDelProyecto() + ".occam";
    //    QString slRutaIndicadaPorUsuario = smRutaDeTrabajo;
    //    if(!slRutaIndicadaPorUsuario.isEmpty()) {
    //        QFile olArchivoALeerEnEditorDeTexto(slRutaIndicadaPorUsuario);
    //        if(olArchivoALeerEnEditorDeTexto.open(QFile::ReadOnly | QFile::Text)) {
    //            QTextStream olTextStreamArchivoLeido(&olArchivoALeerEnEditorDeTexto);
    //            QString text = olTextStreamArchivoLeido.readAll();
    //            olArchivoALeerEnEditorDeTexto.close();
    //            ui->textEdit->setPlainText(text);
    //        }
    //    }
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
    smRutaNombreArchivoDeTrabajo = QFileDialog::getOpenFileName(this, "Abrir proyecto Occam");
    if(!smRutaNombreArchivoDeTrabajo.isEmpty()) {
        QFile olArchivoALeerEnEditorDeTexto(smRutaNombreArchivoDeTrabajo);
        if(olArchivoALeerEnEditorDeTexto.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream olTextStreamArchivoLeido(&olArchivoALeerEnEditorDeTexto);
            QString text = olTextStreamArchivoLeido.readAll();
            olArchivoALeerEnEditorDeTexto.close();
            ui->textEdit->setPlainText(text);
            bmPlantillaOcamAbierta = true;
        }
    }
}
void MainWindow::on_action_Guardar_Proyecto_triggered() {
    QFile olArchivoAGuardarDesdeEditorTexto(smRutaNombreArchivoDeTrabajo);
    if(olArchivoAGuardarDesdeEditorTexto.open(QFile::ReadWrite | QFile::Text )) {
        QTextStream olStreamDeArchivoEscrito(&olArchivoAGuardarDesdeEditorTexto);
        olStreamDeArchivoEscrito << ui->textEdit->toPlainText();
        olArchivoAGuardarDesdeEditorTexto.flush();
        olArchivoAGuardarDesdeEditorTexto.close();
    }
}
void MainWindow::on_actionGuardar_Como_triggered() {
    QString slRutaArhivoIndicadaPorUsuario = QFileDialog::getSaveFileName(this, "Guardar como");
    if(!slRutaArhivoIndicadaPorUsuario.isEmpty()) {
        smRutaNombreArchivoDeTrabajo = slRutaArhivoIndicadaPorUsuario;
        on_action_Guardar_Proyecto_triggered();
    }
}
void MainWindow::on_action_Generar_Plantilla_triggered() {
    QMessageBox olMessageBox;
    if(!bmPlantillaOcamAbierta) {
        olMessageBox.setText("Aún no se ha abierto ninguna plantilla OCCAM");
    }
    else if(!bmPlantillaCompilada) {
        olMessageBox.setText("El la plantilla OCCAM aún no ha sido compilada\n");
    } else {
        if(smRutaNombreArchivoDeTrabajo.isEmpty())
        olMessageBox.setText("Aún no se ha definido la ruta del archivo.");
        else
        olMessageBox.setText("Se exportara proyecto, la ruta completa del archivo es\n" + smRutaNombreArchivoDeTrabajo);
    }
    olMessageBox.exec();
    // Obtener el nombre del proyecto segun archivo con extension Occam
    // Obtener plataforma a generar para el tipo de plantilla
    // Obtener plataforma a generar para el tipo de plantilla
    // Establecer parametros generales y datos para plantilla
}
