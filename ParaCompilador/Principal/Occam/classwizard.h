#ifndef CLASSWIZARD_H
#define CLASSWIZARD_H
#include <QWizard>
#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include "claseproyecto.h"

class ClassWizard : public QWizard {
    Q_OBJECT
public:
    ClassWizard(QWidget *parent = 0);
    void accept() Q_DECL_OVERRIDE;

    bool getPlataforma() {
        return bmEsNetbeans;
    }
    bool getEstaDefinidaPlataforma() {
        return bmPlataformaDefinida;
    }
    QString getRutaCompleta() {
        return smRutaCompleta;
    }

    ClaseProyecto getProyecto() {
        return omProyecto;
    }

protected:
    bool AnalizarCodigo();
    void GenerarProyectoOccam();
private:
    QString smArquitecturaDefinida,
    smNombreDocenteDefinido,
    smFechaDefinida,
    smEntornoDeDesarrolloDefinido,
    smRutaCompleta;
    bool bmEsNetbeans,
    bmPlataformaDefinida;
    ClaseProyecto omProyecto;

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
