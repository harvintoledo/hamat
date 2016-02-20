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
    bn = "";
    ui->textEdit->setPlainText("");
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
    QString pbloc = QFileDialog::getOpenFileName(this, "Abrir proyecto Occam");

    if(!pbloc.isEmpty()) {
        QFile archT(pbloc);
        if(archT.open(QFile::ReadOnly | QFile::Text)) {
            bn = pbloc;
            QTextStream n(&archT);
            QString text = n.readAll();
            archT.close();

            ui->textEdit->setPlainText(text);
        }
    }
}

void MainWindow::on_action_Guardar_Proyecto_triggered() {

    QFile archJ(bn);

    if(archJ.open(QFile::ReadWrite | QFile::Text )) {
        QTextStream stream(&archJ);

        stream << ui->textEdit->toPlainText();
        archJ.flush();
        archJ.close();
    }

}
