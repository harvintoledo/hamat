#include "classwizard.h"
ClassWizard::ClassWizard(QWidget *parent) : QWizard(parent) {
    addPage(new ClasePaginaDeIntroduccion);
    addPage(new ClaseAsistenteNombreProyecto);
    addPage(new ClaseAsistenteEntornoDeDesarrollo);
    addPage(new ClaseAsistenteArquitectura);
    addPage(new ClaseAsistenteDatosDelProyecto);
    addPage(new ClaseAsistenteUbicacionDelProyecto);
    addPage(new ClasePaginaDeConclusion);
    setPixmap(QWizard::BannerPixmap, QPixmap(":Images/banner.png"));
    setPixmap(QWizard::BackgroundPixmap, QPixmap(":Images/background.png"));
    setWindowTitle("Asistente de generador de codigo - Arquitectura de Maquinas III  - UNI");
    smArquitecturaDefinida =
    smNombreDocenteDefinido =
    smFechaDefinida =
    smEntornoDeDesarrolloDefinido =
    bmEsNetbeans =
    bmPlataformaDefinida = false;
}
void ClassWizard::accept() {
    GenerarProyectoOccam();
    QDialog::accept();
}
ClasePaginaDeIntroduccion::ClasePaginaDeIntroduccion(QWidget *parent) : QWizardPage(parent) {
    setTitle(tr("Introduccion"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/Images/watermark1.png"));
    label = new QLabel(tr("Este es un asistente que generara un esqueleto "
    "para definir codigo ensamblador para cualquier herramienta "
    "que simula la ejecucion de procesador. Usted puede escoger "
    "la arquitectura para la que construira el simulador "
    "y el entorno de trabajo, para Netbeans o Miscrosoft Visual C#."));
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}
ClasePaginaDeConclusion::ClasePaginaDeConclusion(QWidget *parent)
: QWizardPage(parent) {
    setTitle(tr("Conclusion"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark2.png"));
    label = new QLabel;
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}
void ClasePaginaDeConclusion::initializePage() {
    QString finishText = wizard()->buttonText(QWizard::FinishButton);
    finishText.remove('&');
    label->setText(tr("Click %1 to generate the class skeleton.")
    .arg(finishText));
}
bool ClassWizard::AnalizarCodigo() {
    bool blResultado = false; // El resultado es verdadero si el codigo se compilo con exito
    // Verificar definiciones y arquitectura
    // Verificar nombre de proyecto
    // Verificar nombre de docente
    // Analizar cuerpo de codigo de definicion de programa
}
void ClaseAsistenteNombreProyecto::initializePage() {
}
ClaseAsistenteNombreProyecto::ClaseAsistenteNombreProyecto(QWidget *parent)
: QWizardPage(parent) {
    setTitle(tr("Nombre del proyecto a generar"));
    setSubTitle(tr("Especifique el nombre del proyecto"
    "para el esqueleto del definidor de codigo."));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/Images/logo1.png"));
    omLabelNombreDelProyecto = new QLabel(tr("&Nombre proyecto:"));
    omEditNombreDelProyecto = new QLineEdit;
    omEditNombreDelProyecto->setText("Simulador");
    omLabelNombreDelProyecto->setBuddy(omEditNombreDelProyecto);
    registerField("omLabelNombreDelProyecto", omLabelNombreDelProyecto);
    registerField("omEditNombreDelProyecto", omEditNombreDelProyecto);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(omLabelNombreDelProyecto, 0, 0);
    layout->addWidget(omEditNombreDelProyecto, 0, 1);
    setLayout(layout);
}
ClaseAsistenteEntornoDeDesarrollo::ClaseAsistenteEntornoDeDesarrollo(QWidget *parent)
: QWizardPage(parent) {
    setTitle(tr("Entorno de desarrollo del proyetcto"));
    setSubTitle(tr("Seleccione el entorno de desarrollo "
    " la plataforma puede ser Visual Studio C# o Java Nebeans o Java Eclipse."));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/Images/logo1.png"));
    omGroupBoxEntornoDesarrollo = new QGroupBox(tr("Entorno de desarrollo"));
    omRadioButtonNetbeans = new QRadioButton(tr("Java Netbeans o Eclipse"));
    omRadioButtonCSharp = new QRadioButton(tr("&Visual Studio C#"));
    omRadioButtonNetbeans->setChecked(true);
    //    connect(omRadioButtonNetbeans, SIGNAL(toggled(bool)),
    //    copyCtorCheckBox, SLOT(setEnabled(bool)));
    registerField("omRadioButtonNetbeans", omRadioButtonNetbeans);
    registerField("omRadioButtonCSharp", omRadioButtonCSharp);
    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    groupBoxLayout->addWidget(omRadioButtonNetbeans);
    groupBoxLayout->addWidget(omRadioButtonCSharp);
    omGroupBoxEntornoDesarrollo->setLayout(groupBoxLayout);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(omGroupBoxEntornoDesarrollo, 3, 0, 1, 2);
    setLayout(layout);
}
ClaseAsistenteArquitectura::ClaseAsistenteArquitectura(QWidget *parent)
: QWizardPage(parent) {
    /*
    QGroupBox *omGroupBoxArquitectura;
    QRadioButton *omRadioButtonArquitectura2Direcciones;
    QRadioButton *omRadioButtonArquitectura3Direcciones;
    QRadioButton *omRadioButtonArquitecturaPila;
    * */
    setTitle(tr("Entorno de desarrollo del proyetcto"));
    setSubTitle(tr("Seleccione el entorno de desarrollo "
    " la plataforma puede ser Visual Studio C# o Java Nebeans o Java Eclipse."));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/Images/logo1.png"));
    omGroupBoxArquitectura = new QGroupBox(tr("Arquitectura"));
    omRadioButtonArquitectura2Direcciones = new QRadioButton(tr("Arquitectura de 2 direcciones"));
    omRadioButtonArquitectura3Direcciones = new QRadioButton(tr("Arquitectura de 3 direcciones"));
    omRadioButtonArquitecturaPila = new QRadioButton(tr("Arquitectura de pila"));
    omRadioButtonArquitectura2Direcciones->setChecked(true);
    //    connect(omRadioButtonNetbeans, SIGNAL(toggled(bool)),
    //    copyCtorCheckBox, SLOT(setEnabled(bool)));
    registerField("omRadioButtonArquitectura2Direcciones", omRadioButtonArquitectura2Direcciones);
    registerField("omRadioButtonArquitectura3Direcciones", omRadioButtonArquitectura3Direcciones);
    registerField("omRadioButtonArquitecturaPila", omRadioButtonArquitecturaPila);
    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    groupBoxLayout->addWidget(omRadioButtonArquitectura2Direcciones);
    groupBoxLayout->addWidget(omRadioButtonArquitectura3Direcciones);
    groupBoxLayout->addWidget(omRadioButtonArquitecturaPila);
    omGroupBoxArquitectura->setLayout(groupBoxLayout);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(omGroupBoxArquitectura, 3, 0, 1, 2);
    setLayout(layout);
}
ClaseAsistenteDatosDelProyecto::ClaseAsistenteDatosDelProyecto(QWidget *parent)
: QWizardPage(parent) {
    setTitle(tr("Datos del proyecto a generar"));
    setSubTitle(tr("Especifique el nombre del docente "
    "y los integrantes(al menos uno) del proyecto."));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/Images/logo1.png"));
    omLabelNombreDocente = new QLabel(tr("Nombre del &Docente:"));
    omLabelNombreIntegrante1 = new QLabel(tr("Integrante &1:"));
    omLabelNombreIntegrante2 = new QLabel(tr("Integrante &2:"));
    omLabelNombreIntegrante3 = new QLabel(tr("Integrante &3:"));
    omLabelNombreIntegrante4 = new QLabel(tr("Integrante &4:"));
    omLabelNombreIntegrante5 = new QLabel(tr("Integrante &5:"));
    omLabelNombreIntegrante6 = new QLabel(tr("Integrante &6:"));
    omLineEditNombreDocente = new QLineEdit;
    omLineEditNombreIntegrante1 = new QLineEdit;
    omLineEditNombreIntegrante2 = new QLineEdit;
    omLineEditNombreIntegrante3 = new QLineEdit;
    omLineEditNombreIntegrante4 = new QLineEdit;
    omLineEditNombreIntegrante5 = new QLineEdit;
    omLineEditNombreIntegrante6 = new QLineEdit;
    omLabelNombreDocente->setBuddy(omLineEditNombreDocente);
    omLabelNombreIntegrante1->setBuddy(omLineEditNombreIntegrante1);
    omLabelNombreIntegrante2->setBuddy(omLineEditNombreIntegrante2);
    omLabelNombreIntegrante3->setBuddy(omLineEditNombreIntegrante3);
    omLabelNombreIntegrante4->setBuddy(omLineEditNombreIntegrante4);
    omLabelNombreIntegrante5->setBuddy(omLineEditNombreIntegrante5);
    omLabelNombreIntegrante6->setBuddy(omLineEditNombreIntegrante6);
    groupBox = new QGroupBox(tr("C&onstructor"));
    registerField("omLabelNombreDocente", omLabelNombreDocente);
    registerField("omLabelNombreIntegrante1", omLabelNombreIntegrante1);
    registerField("omLabelNombreIntegrante2", omLabelNombreIntegrante2);
    registerField("omLabelNombreIntegrante3", omLabelNombreIntegrante3);
    registerField("omLabelNombreIntegrante4", omLabelNombreIntegrante4);
    registerField("omLabelNombreIntegrante5", omLabelNombreIntegrante5);
    registerField("omLabelNombreIntegrante6", omLabelNombreIntegrante6);
    registerField("omLineEditNombreDocente", omLineEditNombreDocente);
    registerField("omLineEditNombreIntegrante1", omLineEditNombreIntegrante1);
    registerField("omLineEditNombreIntegrante2", omLineEditNombreIntegrante2);
    registerField("omLineEditNombreIntegrante3", omLineEditNombreIntegrante3);
    registerField("omLineEditNombreIntegrante4", omLineEditNombreIntegrante4);
    registerField("omLineEditNombreIntegrante5", omLineEditNombreIntegrante5);
    registerField("omLineEditNombreIntegrante6", omLineEditNombreIntegrante6);
    //    groupBox->setLayout(groupBoxLayout);
    QGridLayout *layoutIntegrantes = new QGridLayout;
    layoutIntegrantes->addWidget(omLabelNombreDocente, 1, 0);
    layoutIntegrantes->addWidget(omLineEditNombreDocente, 1, 1);
    layoutIntegrantes->addWidget(omLabelNombreIntegrante1, 2, 0);
    layoutIntegrantes->addWidget(omLineEditNombreIntegrante1, 2, 1);
    layoutIntegrantes->addWidget(omLabelNombreIntegrante2, 3, 0);
    layoutIntegrantes->addWidget(omLineEditNombreIntegrante2, 3, 1);
    layoutIntegrantes->addWidget(omLabelNombreIntegrante3, 4, 0);
    layoutIntegrantes->addWidget(omLineEditNombreIntegrante3, 4, 1);
    layoutIntegrantes->addWidget(omLabelNombreIntegrante4, 5, 0);
    layoutIntegrantes->addWidget(omLineEditNombreIntegrante4, 5, 1);
    layoutIntegrantes->addWidget(omLabelNombreIntegrante5, 6, 0);
    layoutIntegrantes->addWidget(omLineEditNombreIntegrante5, 6, 1);
    layoutIntegrantes->addWidget(omLabelNombreIntegrante6, 7, 0);
    layoutIntegrantes->addWidget(omLineEditNombreIntegrante6, 7, 1);
    //    layout->addWidget(qobjectMacroCheckBox, 2, 0, 1, 2);
    //    layout->addWidget(groupBox, 3, 0, 1, 2);
    setLayout(layoutIntegrantes);
}
void ClaseAsistenteUbicacionDelProyecto::initializePage() {
    /*
    *     QLabel *omLabelDirectorioDeUbicacionDelProyectoPorDefecto;
    QLineEdit *omLineEditDirectorioDeUbicacionDelProyectoPorDefecto;
    * */
    QString className = field("className").toString();/*
    headerLineEdit->setText(className.toLower() + ".h");
    implementationLineEdit->setText(className.toLower() + ".cpp");*/
    omLabelDirectorioDeUbicacionDelProyectoPorDefecto->setText("Ubicacion del proyecto:");
    omLineEditDirectorioDeUbicacionDelProyectoPorDefecto->setText(QDir::toNativeSeparators(QDir::tempPath()));
    omLabelDirectorioDeUbicacionDelProyectoPorDefecto->setBuddy(omLineEditDirectorioDeUbicacionDelProyectoPorDefecto);
}
ClaseAsistenteUbicacionDelProyecto::ClaseAsistenteUbicacionDelProyecto(QWidget *parent)
: QWizardPage(parent)
{
    setTitle(tr("Archivos generados"));
    setSubTitle(tr("Especificar el directorio donde se quiere el proyecto "
    "skeleton code."));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo3.png"));
    omLabelDirectorioDeUbicacionDelProyectoPorDefecto = new QLabel(tr("&Ubicacion del proyecto:"));
    omLineEditDirectorioDeUbicacionDelProyectoPorDefecto = new QLineEdit;
    omLabelDirectorioDeUbicacionDelProyectoPorDefecto->setBuddy(omLineEditDirectorioDeUbicacionDelProyectoPorDefecto);
    registerField("omLabelDirectorioDeUbicacionDelProyectoPorDefecto", omLabelDirectorioDeUbicacionDelProyectoPorDefecto);
    registerField("omLineEditDirectorioDeUbicacionDelProyectoPorDefecto", omLineEditDirectorioDeUbicacionDelProyectoPorDefecto);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(omLabelDirectorioDeUbicacionDelProyectoPorDefecto, 0, 0);
    layout->addWidget(omLineEditDirectorioDeUbicacionDelProyectoPorDefecto, 0, 1);
    setLayout(layout);
}
void ClassWizard::GenerarProyectoOccam() {
    QString slFechaGeneracionDeProyecto = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    QByteArray block;
    ClaseMiembroProyecto olMiembro;
    ClaseMiembroProyecto olIntegrante;
    if(!field("omEditNombreDelProyecto").toByteArray().isEmpty()) {
        omProyecto.setNombreProyecto(field("omEditNombreDelProyecto").toString());
    }
    else {
        omProyecto.setNombreProyecto("ProyectoSinNombre");
    }
    if(!field("omLineEditDirectorioDeUbicacionDelProyectoPorDefecto").toByteArray().isEmpty()) {
        omProyecto.setUbicacionDirectorio(field("omLineEditDirectorioDeUbicacionDelProyectoPorDefecto").toString());
    }
    else {
        omProyecto.setUbicacionDirectorio("C:\\Users\\Public");
    }
    omProyecto.setFechaDeGeneradoProyecto(slFechaGeneracionDeProyecto);
    if (field("omRadioButtonNetbeans").toBool()) {
        omProyecto.setPlataforma(ClaseProyecto::TP_JAVA_NETBEANS_O_ECLIPSE);
    }
    else if (field("omRadioButtonCSharp").toBool()) {
        omProyecto.setPlataforma(ClaseProyecto::TP_CSHARP_VISUAL_STUDIO);
    }
    else {
        omProyecto.setPlataforma(ClaseProyecto::TP_NINGUNA_PLATAFORMA);
    }
    if(!field("omLineEditNombreDocente").toByteArray().isEmpty()) {
        olMiembro.setNombre(field("omLineEditNombreDocente").toString());
        omProyecto.setMiembroProyecto(olMiembro);
    }
    if(!field("omLineEditNombreIntegrante1").toByteArray().isEmpty()) {
        olIntegrante.setNombre(field("omLineEditNombreIntegrante1").toString());
        omProyecto.setIntegrante1(olIntegrante);
    }
    if(!field("omLineEditNombreIntegrante2").toByteArray().isEmpty()) {
        olIntegrante.setNombre(field("omLineEditNombreIntegrante1").toString());
        omProyecto.setIntegrante1(olIntegrante);
    }
    if(!field("omLineEditNombreIntegrante3").toByteArray().isEmpty()) {
        olIntegrante.setNombre(field("omLineEditNombreIntegrante1").toString());
        omProyecto.setIntegrante1(olIntegrante);
    }
    if(!field("omLineEditNombreIntegrante4").toByteArray().isEmpty()) {
        olIntegrante.setNombre(field("omLineEditNombreIntegrante1").toString());
        omProyecto.setIntegrante1(olIntegrante);
    }
    if(!field("omLineEditNombreIntegrante5").toByteArray().isEmpty()) {
        olIntegrante.setNombre(field("omLineEditNombreIntegrante1").toString());
        omProyecto.setIntegrante1(olIntegrante);
    }
    if(!field("omLineEditNombreIntegrante6").toByteArray().isEmpty()) {
        olIntegrante.setNombre(field("omLineEditNombreIntegrante1").toString());
        omProyecto.setIntegrante1(olIntegrante);
    }
    if (field("omRadioButtonArquitectura2Direcciones").toBool()) {
        block += ".ARQUITECTURA\n";
        block += "DOSDIRECCIONES\n";
        omProyecto.setTipoArquitectura(ClaseProyecto::TA_DOS_DIRECCIONES);
    }
    else if (field("omRadioButtonArquitectura3Direcciones").toBool()) {
        block += ".ARQUITECTURA\n";
        block += "TRESDIRECCIONES\n";
        omProyecto.setTipoArquitectura(ClaseProyecto::TA_TRES_DIRECCIONES);
    }
    else if (field("omRadioButtonArquitecturaPila").toBool()) {
        block += ".ARQUITECTURA\n";
        block += "PILA\n";
        omProyecto.setTipoArquitectura(ClaseProyecto::TA_PILA);
    }
    else {
        omProyecto.setTipoArquitectura(ClaseProyecto::TA_NINGUNA_ARQUITECTURA);
    }
}
