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

class ClassWizard : public QWizard {
    Q_OBJECT

public:
    ClassWizard(QWidget *parent = 0);

    void accept() Q_DECL_OVERRIDE;
protected:
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
    QString smNombreArchivo,
    smArquitecturaDefinida,
    smNombreDocenteDefinido,
    smFechaDefinida,
    smEntornoDeDesarrolloDefinido,
    smAsignaturaDefinida,
    smTemaDefinido;

};

class IntroPage : public QWizardPage {
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);

private:
    QLabel *label;
};

class ClassInfoPage : public QWizardPage {
    Q_OBJECT

public:
    ClassInfoPage(QWidget *parent = 0);

private:
    QLabel *classNameLabel;
    QLabel *baseClassLabel;
    QLineEdit *classNameLineEdit;
    QLineEdit *baseClassLineEdit;
    QCheckBox *qobjectMacroCheckBox;
    QGroupBox *groupBox;
    QRadioButton *qobjectCtorRadioButton;
    QRadioButton *qwidgetCtorRadioButton;
    QRadioButton *defaultCtorRadioButton;
    QCheckBox *copyCtorCheckBox;
};

class CodeStylePage : public QWizardPage {
    Q_OBJECT

public:
    CodeStylePage(QWidget *parent = 0);

protected:
    void initializePage() Q_DECL_OVERRIDE;

private:
    QCheckBox *commentCheckBox;
    QCheckBox *protectCheckBox;
    QCheckBox *includeBaseCheckBox;
    QLabel *macroNameLabel;
    QLabel *baseIncludeLabel;
    QLineEdit *macroNameLineEdit;
    QLineEdit *baseIncludeLineEdit;
};

class OutputFilesPage : public QWizardPage {
    Q_OBJECT

public:
    OutputFilesPage(QWidget *parent = 0);

protected:
    void initializePage() Q_DECL_OVERRIDE;

private:
    QLabel *outputDirLabel;
    QLabel *headerLabel;
    QLabel *implementationLabel;
    QLineEdit *outputDirLineEdit;
    QLineEdit *headerLineEdit;
    QLineEdit *implementationLineEdit;
};

class ConclusionPage : public QWizardPage {
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);

protected:
    void initializePage() Q_DECL_OVERRIDE;

private:
    QLabel *label;
};

#endif // CLASSWIZARD_H
