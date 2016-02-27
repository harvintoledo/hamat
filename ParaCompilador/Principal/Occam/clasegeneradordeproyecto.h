#ifndef CLASEGENERADORDEPROYECTO_H
#define CLASEGENERADORDEPROYECTO_H

#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QMessageBox>
#include <QDebug>
#include "claseproyecto.h"
#include "util.h"
class ClaseGeneradorDeProyecto {
public:
    ClaseGeneradorDeProyecto();
    void setProyecto(ClaseProyecto opProyecto) {
        omProyecto = opProyecto;
    }
    ClaseProyecto getProyecto() {
        return omProyecto;
    }
    void GenerarNetbeans();
    void GenerarCSharp();
    void GenerarProyectoOccam();
private:
    void setWord(QString);
    void GeneraProyectoCompletoParaCSharp(QString);
    void GeneraProyectoCompletoParaJavaMaven(QString);
    void GenerarAnalizadorNetBeans(QString);
    void GenerarArchivoPom(QString);
    void GenerarMemoriaNetBeans(QString);
    void GenerarMainNetBeans(QString);
    void GenerarCLSAnalizadorCSharp(QString);
    void GenerarCLSMemoriaCSharp(QString);
    void GenerarPlantillaDeProyectoCSharp(QString);
    void GenerarArchivoProgramCSharp(QString);
    void GenerarArchivoAppConfigCSharp(QString);
    void GenerarArchivoForm1CSharp(QString);
    void GenerarArchivoForm1DesignerCSharp(QString);
    void GenerarArchivoAssemblyInfoEnPropertiesCSharp(QString);
    void GenerarArchivoResourceDesignerEnPropertiesCSharp(QString);
    void GenerarArchivoResourceResxEnPropertiesCSharp(QString);
    void GenerarArchivoSettingsDesignerEnPropertiesCSharp(QString);
    void GenerarArchivoSettingsSettingsEnPropertiesCSharp(QString);
    void GenerarArchivoDeSolucionDelProyectoCSharp(QString);
private:
    ClaseProyecto omProyecto;
    QByteArray omBlockProyectoOccam;
};

#endif // CLASEGENERADORDEPROYECTO_H
