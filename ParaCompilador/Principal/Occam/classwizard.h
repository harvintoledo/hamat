#ifndef CLASSWIZARD_H
#define CLASSWIZARD_H
#include <QWizard>
#include <QCheckBox>
#include <QDir>
#include <QFile>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QDateTime>
class ClassWizard : public QWizard {
    Q_OBJECT
public:
    ClassWizard(QWidget *parent = 0);
    void accept() Q_DECL_OVERRIDE;
    QString getNombreDelProyecto() {
        return smNombreDelProyecto;
    }
    void setNombreDelProyecto(QString spNombreDelProyecto) {
        smNombreDelProyecto = spNombreDelProyecto;
    }
    QString getUbicacionDelProyecto() {
        return smUbicacionDelProyecto;
    }
    void setUbicacionDelProyecto(QString spUbicacionDelProyecto) {
        smUbicacionDelProyecto = spUbicacionDelProyecto;
    }
    void GenerarNetbeans();
    void GenerarCSharp();
    bool getPlataforma() {
        return bmEsNetbeans;
    }
    bool getEstaDefinidaPlataforma() {
        return bmPlataformaDefinida;
    }
    QString getRutaCompleta() {
        return smRutaCompleta;
    }

protected:
    void GenerarProyectoOccam(QString);
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
    bool AnalizarCodigo();

private:
    QString smNombreDelProyecto,
    smUbicacionDelProyecto,
    smArquitecturaDefinida,
    smNombreDocenteDefinido,
    smFechaDefinida,
    smEntornoDeDesarrolloDefinido,
    smAsignaturaDefinida,
    smTemaDefinido,
    smRutaCompleta;
    QByteArray omBlockProyectoOccam,
    omBlockPlantillaCSharpJava;
    bool bmEsNetbeans,
    bmPlataformaDefinida;
};
class ClasePaginaDeIntroduccion : public QWizardPage {
    Q_OBJECT
public:
    ClasePaginaDeIntroduccion(QWidget *parent = 0);
private:
    QLabel *label;
};
class ClasePaginaDeConclusion : public QWizardPage {
    Q_OBJECT
public:
    ClasePaginaDeConclusion(QWidget *parent = 0);
protected:
    void initializePage() Q_DECL_OVERRIDE;
private:
    QLabel *label;
};
class ClaseAsistenteNombreProyecto : public QWizardPage {
    Q_OBJECT
public:
    ClaseAsistenteNombreProyecto(QWidget *parent = 0);
protected:
    void initializePage() Q_DECL_OVERRIDE;
private:
    QLabel *omLabelNombreDelProyecto;
    QLineEdit *omEditNombreDelProyecto;
};
class ClaseAsistenteEntornoDeDesarrollo : public QWizardPage {
    Q_OBJECT
public:
    ClaseAsistenteEntornoDeDesarrollo(QWidget *parent = 0);
private:
    QGroupBox *omGroupBoxEntornoDesarrollo;
    QRadioButton *omRadioButtonNetbeans;
    QRadioButton *omRadioButtonCSharp;
};
class ClaseAsistenteArquitectura : public QWizardPage {
    Q_OBJECT
public:
    ClaseAsistenteArquitectura(QWidget *parent = 0);
private:
    QGroupBox *omGroupBoxArquitectura;
    QRadioButton *omRadioButtonArquitectura2Direcciones;
    QRadioButton *omRadioButtonArquitectura3Direcciones;
    QRadioButton *omRadioButtonArquitecturaPila;
};
class ClaseAsistenteDatosDelProyecto : public QWizardPage {
    Q_OBJECT
public:
    ClaseAsistenteDatosDelProyecto(QWidget *parent = 0);
private:
    QLabel *omLabelNombreDocente;
    QLabel *omLabelNombreIntegrante1;
    QLabel *omLabelNombreIntegrante2;
    QLabel *omLabelNombreIntegrante3;
    QLabel *omLabelNombreIntegrante4;
    QLabel *omLabelNombreIntegrante5;
    QLabel *omLabelNombreIntegrante6;
    QLineEdit *omLineEditNombreDocente;
    QLineEdit *omLineEditNombreIntegrante1;
    QLineEdit *omLineEditNombreIntegrante2;
    QLineEdit *omLineEditNombreIntegrante3;
    QLineEdit *omLineEditNombreIntegrante4;
    QLineEdit *omLineEditNombreIntegrante5;
    QLineEdit *omLineEditNombreIntegrante6;
    QGroupBox *groupBox;
    QGroupBox *groupBoxDocente;
    QGroupBox *groupBoxIntegrantes;
};
class ClaseAsistenteUbicacionDelProyecto : public QWizardPage {
    Q_OBJECT
public:
    ClaseAsistenteUbicacionDelProyecto(QWidget *parent = 0);
protected:
    void initializePage() Q_DECL_OVERRIDE;
private:
    QLabel *omLabelDirectorioDeUbicacionDelProyectoPorDefecto;
    QLineEdit *omLineEditDirectorioDeUbicacionDelProyectoPorDefecto;
};
#endif // CLASSWIZARD_H
