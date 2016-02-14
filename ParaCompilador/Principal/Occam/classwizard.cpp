#include "classwizard.h"
ClassWizard::ClassWizard(QWidget *parent) : QWizard(parent) {
    addPage(new IntroPage);
    addPage(new ClassInfoPage);
    addPage(new CodeStylePage);
    addPage(new OutputFilesPage);
    addPage(new ConclusionPage);
    setPixmap(QWizard::BannerPixmap, QPixmap(":Images/banner.png"));
    setPixmap(QWizard::BackgroundPixmap, QPixmap(":Images/background.png"));
    setWindowTitle("Asistente de generador de codigo - Arquitectura de Maquinas III  - UNI");
    smArquitecturaDefinida =
        smNombreDocenteDefinido =
        smFechaDefinida =
        smEntornoDeDesarrolloDefinido =
        smAsignaturaDefinida =
        smTemaDefinido = "";
}
void ClassWizard::accept() {
    QByteArray className = field("className").toByteArray();
    QByteArray baseClass = field("baseClass").toByteArray();
    smNombreArchivo = QString("%1").arg(field("className").toString());
    QByteArray macroName = field("macroName").toByteArray();
    QByteArray baseInclude = field("baseInclude").toByteArray();
    QString outputDir = field("outputDir").toString();
    QString header = field("header").toString();
    QString implementation = field("implementation").toString();
    QByteArray block;
//    GeneraProyectoCompletoParaJavaMaven(outputDir);
    GeneraProyectoCompletoParaCSharp(outputDir);
    QDialog::accept();
}

void ClassWizard::GeneraProyectoCompletoParaCSharp(QString outputDir){
    bool blResultadoCreacionDeDirectorio = false;
    QDir olDirectorioProyecto(QString("%1/%2").arg(outputDir).arg(smNombreArchivo));

    // Crear directorio donde estan los archivos principales de ensamblador
    if(!olDirectorioProyecto.exists()) {
        if(olDirectorioProyecto.mkdir(QString("%1/%2CS").arg(outputDir).arg(smNombreArchivo))) {
            olDirectorioProyecto.setPath(QString("%1/%2CS/%2CS")
                                         .arg(outputDir)
                                         .arg(smNombreArchivo));
            if(!olDirectorioProyecto.exists()) {
                if(olDirectorioProyecto.mkdir(QString("%1/%2CS/%2CS")
                                              .arg(outputDir)
                                              .arg(smNombreArchivo))) {
                    olDirectorioProyecto.setPath(QString("%1/%2CS/%2CS/%2")
                                                 .arg(outputDir)
                                                 .arg(smNombreArchivo));
                     if(!olDirectorioProyecto.exists()) {
                         if(olDirectorioProyecto.mkdir(QString("%1/%2CS/%2CS/%2")
                                 .arg(outputDir)
                                 .arg(smNombreArchivo)))
                             blResultadoCreacionDeDirectorio = true;
                     }

                }
            }
        }
    }
    GenerarCLSAnalizadorCSharp(olDirectorioProyecto.absolutePath());
    GenerarCLSMemoriaCSharp(olDirectorioProyecto.absolutePath());
    olDirectorioProyecto.setPath(QString("%1/%2CS/%2CS")
                                 .arg(outputDir)
                                 .arg(smNombreArchivo));
    GenerarPlantillaDeProyectoCSharp(olDirectorioProyecto.absolutePath());
    GenerarArchivoProgramCSharp(olDirectorioProyecto.absolutePath());
    GenerarArchivoAppConfigCSharp(olDirectorioProyecto.absolutePath());
    GenerarArchivoForm1CSharp(olDirectorioProyecto.absolutePath());
    GenerarArchivoForm1DesignerCSharp(olDirectorioProyecto.absolutePath());
    olDirectorioProyecto.setPath(QString("%1/%2CS/%2CS/Properties")
                                 .arg(outputDir)
                                 .arg(smNombreArchivo));
    if(!olDirectorioProyecto.exists()) {
        if(olDirectorioProyecto.mkdir(QString("%1/%2CS/%2CS/Properties")
                                      .arg(outputDir)
                                      .arg(smNombreArchivo))) {
            blResultadoCreacionDeDirectorio = true;
        }
    }
    // Crear archivos de propiedades
    GenerarArchivoAssemblyInfoEnPropertiesCSharp(olDirectorioProyecto.absolutePath());
    GenerarArchivoResourceDesignerEnPropertiesCSharp(olDirectorioProyecto.absolutePath());
    GenerarArchivoResourceResxEnPropertiesCSharp(olDirectorioProyecto.absolutePath());
    GenerarArchivoSettingsDesignerEnPropertiesCSharp(olDirectorioProyecto.absolutePath());
    GenerarArchivoSettingsSettingsEnPropertiesCSharp(olDirectorioProyecto.absolutePath());

    // Finalmente generar el archivo de solucion del proyecto
    // Ubicarse en la raiz del directorio del proyecto para ubicar el archivo de solucion
    olDirectorioProyecto.setPath(QString("%1/%2CS")
                                 .arg(outputDir)
                                 .arg(smNombreArchivo));
    GenerarArchivoDeSolucionDelProyectoCSharp(olDirectorioProyecto.absolutePath());

}
void ClassWizard::GeneraProyectoCompletoParaJavaMaven(QString outputDir){
    bool blResultadoCreacionDeDirectorio = false;
    QDir olDirectorioProyecto(QString("%1/%2").arg(outputDir).arg(smNombreArchivo));
    if(!olDirectorioProyecto.exists()) {
        if(olDirectorioProyecto.mkdir(QString("%1/%2").arg(outputDir).arg(smNombreArchivo))) {
            olDirectorioProyecto.setPath(QString("%1/%2/src").arg(outputDir).arg(smNombreArchivo));
            if(!olDirectorioProyecto.exists()) {
                if(olDirectorioProyecto.mkdir(QString("%1/%2/src").arg(outputDir).arg(smNombreArchivo))) {
                    olDirectorioProyecto.setPath(QString("%1/%2/src/main").arg(outputDir).arg(smNombreArchivo));
                    if(!olDirectorioProyecto.exists()) {
                        if(olDirectorioProyecto.mkdir(QString("%1/%2/src/main").arg(outputDir).arg(smNombreArchivo))) {
                            olDirectorioProyecto.setPath(QString("%1/%2/src/main/java").arg(outputDir).arg(smNombreArchivo));
                            if(!olDirectorioProyecto.exists()) {
                                if(olDirectorioProyecto.mkdir(QString("%1/%2/src/main/java").arg(outputDir).arg(smNombreArchivo))) {
                                    olDirectorioProyecto.setPath(QString("%1/%2/src/main/java/org").arg(outputDir).arg(smNombreArchivo));
                                    if(!olDirectorioProyecto.exists()) {
                                        if(olDirectorioProyecto.mkdir(QString("%1/%2/src/main/java/org").arg(outputDir).arg(smNombreArchivo))) {
                                            olDirectorioProyecto.setPath(QString("%1/%2/src/main/java/org/%3").arg(outputDir).arg(smNombreArchivo).arg(smNombreArchivo.toLower()));
                                            if(!olDirectorioProyecto.exists()) {
                                                if(olDirectorioProyecto.mkdir(QString("%1/%2/src/main/java/org/%3").arg(outputDir).arg(smNombreArchivo).arg(smNombreArchivo.toLower())))
                                                blResultadoCreacionDeDirectorio = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    GenerarAnalizadorNetBeans(olDirectorioProyecto.absolutePath());
    GenerarMemoriaNetBeans(olDirectorioProyecto.absolutePath());
    GenerarMainNetBeans(olDirectorioProyecto.absolutePath());
    GenerarArchivoPom(outputDir);
}

IntroPage::IntroPage(QWidget *parent) : QWizardPage(parent) {
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
ClassInfoPage::ClassInfoPage(QWidget *parent)
: QWizardPage(parent) {
    setTitle(tr("Informacion del proyecto a generar"));
    setSubTitle(tr("Especifique la informacion basica "
    "para el esqueleto del definidor de codigo."));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/Images/logo1.png"));
    classNameLabel = new QLabel(tr("&Nombre proyecto:"));
    classNameLineEdit = new QLineEdit;
    classNameLineEdit->setText("SimuladorDosDirecciones");
    classNameLabel->setBuddy(classNameLineEdit);
    baseClassLabel = new QLabel(tr("Nombre definidor:"));
    baseClassLineEdit = new QLineEdit;
    baseClassLineEdit->setText("definidor.defi");
    baseClassLabel->setBuddy(baseClassLineEdit);
    qobjectMacroCheckBox = new QCheckBox(tr("Escoger arquitectura"));
    groupBox = new QGroupBox(tr("C&onstructor"));
    qobjectCtorRadioButton = new QRadioButton(tr("Arquitectura de &dos direcciones"));
    qwidgetCtorRadioButton = new QRadioButton(tr("&Arquitectura de &tres direccciones"));
    defaultCtorRadioButton = new QRadioButton(tr("&Arquitectura de &pila"));
    copyCtorCheckBox = new QCheckBox(tr("&Generar plantilla de ayuda"));
    defaultCtorRadioButton->setChecked(true);
    connect(defaultCtorRadioButton, SIGNAL(toggled(bool)),
    copyCtorCheckBox, SLOT(setEnabled(bool)));
    registerField("className*", classNameLineEdit);
    registerField("baseClass", baseClassLineEdit);
    registerField("qobjectMacro", qobjectMacroCheckBox);
    registerField("qobjectCtor", qobjectCtorRadioButton);
    registerField("qwidgetCtor", qwidgetCtorRadioButton);
    registerField("defaultCtor", defaultCtorRadioButton);
    registerField("copyCtor", copyCtorCheckBox);
    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    groupBoxLayout->addWidget(qobjectCtorRadioButton);
    groupBoxLayout->addWidget(qwidgetCtorRadioButton);
    groupBoxLayout->addWidget(defaultCtorRadioButton);
    groupBoxLayout->addWidget(copyCtorCheckBox);
    groupBox->setLayout(groupBoxLayout);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(classNameLabel, 0, 0);
    layout->addWidget(classNameLineEdit, 0, 1);
    layout->addWidget(baseClassLabel, 1, 0);
    layout->addWidget(baseClassLineEdit, 1, 1);
    layout->addWidget(qobjectMacroCheckBox, 2, 0, 1, 2);
    layout->addWidget(groupBox, 3, 0, 1, 2);
    setLayout(layout);
}
CodeStylePage::CodeStylePage(QWidget *parent) : QWizardPage(parent) {
    setTitle(tr("Code Style Options"));
    setSubTitle(tr("Choose the formating of the generated code."));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/Images/logo2.png"));
    commentCheckBox = new QCheckBox("&Start generated files with a ");
    commentCheckBox->setChecked(true);
    protectCheckBox = new QCheckBox("tr(&Protect header file against multple "
    "inclusion");
    protectCheckBox->setChecked(true);
    macroNameLabel = new QLabel(tr("&Macro name:"));
    macroNameLineEdit = new QLineEdit;
    macroNameLabel->setBuddy(macroNameLineEdit);
    includeBaseCheckBox = new QCheckBox(tr("&Include class definition"));
    baseIncludeLabel = new QLabel(tr("Base class include:"));
    baseIncludeLineEdit = new QLineEdit;
    baseIncludeLabel->setBuddy(baseIncludeLineEdit);
    connect(protectCheckBox, SIGNAL(toggled(bool)),
    macroNameLabel, SLOT(setEnabled(bool)));
    connect(protectCheckBox, SIGNAL(toggled(bool)),
    macroNameLineEdit, SLOT(setEnabled(bool)));
    connect(includeBaseCheckBox, SIGNAL(toggled(bool)),
    baseIncludeLabel, SLOT(setEnabled(bool)));
    connect(includeBaseCheckBox, SIGNAL(toggled(bool)),
    baseIncludeLineEdit, SLOT(setEnabled(bool)));
    QGridLayout *layout = new QGridLayout;
    layout->setColumnMinimumWidth(0, 20);
    layout->addWidget(commentCheckBox, 0, 0, 1, 3);
    layout->addWidget(protectCheckBox, 1, 0, 1, 3);
    layout->addWidget(macroNameLabel, 2, 1);
    layout->addWidget(macroNameLineEdit, 2, 2);
    layout->addWidget(includeBaseCheckBox, 3, 0, 1, 3);
    layout->addWidget(baseIncludeLabel, 4, 1);
    layout->addWidget(baseIncludeLineEdit, 4, 2);
    setLayout(layout);
}
void CodeStylePage::initializePage() {
    QString className = field("className").toString();
    macroNameLineEdit->setText(className.toUpper()+ "_H");
    QString baseClass = field("baseClass").toString();
    includeBaseCheckBox->setChecked(!baseClass.isEmpty());
    includeBaseCheckBox->setEnabled(!baseClass.isEmpty());
    baseIncludeLabel->setEnabled(!baseClass.isEmpty());
    baseIncludeLineEdit->setEnabled(!baseClass.isEmpty());
    if(baseClass.isEmpty()) {
        baseIncludeLineEdit->clear();
    }
    else if(QRegExp("Q[A-Z].*").exactMatch(baseClass)) {
        baseIncludeLineEdit->setText("<" + baseClass + ">");
    }
    else {
        baseIncludeLineEdit->setText("\"" + baseClass.toLower() + ".h\"");
    }
}
OutputFilesPage::OutputFilesPage(QWidget *parent)
: QWizardPage(parent)
{
    setTitle(tr("Archivos generados"));
    setSubTitle(tr("Especificar el directorio donde se quiere el proyecto "
    "skeleton code."));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo3.png"));
    outputDirLabel = new QLabel(tr("&Salida directorio:"));
    outputDirLineEdit = new QLineEdit;
    outputDirLabel->setBuddy(outputDirLineEdit);
    headerLabel = new QLabel(tr("&Header file name:"));
    headerLineEdit = new QLineEdit;
    headerLabel->setBuddy(headerLineEdit);
    implementationLabel = new QLabel(tr("&Implementation file name:"));
    implementationLineEdit = new QLineEdit;
    implementationLabel->setBuddy(implementationLineEdit);
    registerField("outputDir*", outputDirLineEdit);
    registerField("header*", headerLineEdit);
    registerField("implementation*", implementationLineEdit);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(outputDirLabel, 0, 0);
    layout->addWidget(outputDirLineEdit, 0, 1);
    layout->addWidget(headerLabel, 1, 0);
    layout->addWidget(headerLineEdit, 1, 1);
    layout->addWidget(implementationLabel, 2, 0);
    layout->addWidget(implementationLineEdit, 2, 1);
    setLayout(layout);
}
void OutputFilesPage::initializePage() {
    QString className = field("className").toString();
    headerLineEdit->setText(className.toLower() + ".h");
    implementationLineEdit->setText(className.toLower() + ".cpp");
    outputDirLineEdit->setText(QDir::toNativeSeparators(QDir::tempPath()));
}
ConclusionPage::ConclusionPage(QWidget *parent)
: QWizardPage(parent) {
    setTitle(tr("Conclusion"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark2.png"));
    label = new QLabel;
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}
void ConclusionPage::initializePage() {
    QString finishText = wizard()->buttonText(QWizard::FinishButton);
    finishText.remove('&');
    label->setText(tr("Click %1 to generate the class skeleton.")
    .arg(finishText));
}
void ClassWizard::GenerarAnalizadorNetBeans(QString outputDir) {
    QByteArray block;
    QString slPackageName = "org";
    QFile headerFile(outputDir + "/" + "Analizador" + ".java");
    block += "/*\n";
    block += "* *********************************************************************************\n";
    block += "* ***                                                                           ***\n";
    block += "* *** Programa que emula memoria y conjunto de instrucciones de dos direcciones ***\n";
    block += "* *** Plantilla Generada por Ocamm                                              ***\n";
    block += "* *** Integrantes                                                               ***\n";
    block += "* *** Jorge Manuel Potosme Alvarez                                              ***\n";
    block += "* *** Harvin Manuel Toledo Polanco                                              ***\n";
    block += "* *** Domingo 7 de febrero de 2016                                              ***\n";
    block += "* ***                                                                           ***\n";
    block += "* *********************************************************************************\n";
    block += "* */\n";
    block += "package " + slPackageName + "." + smNombreArchivo + ";\n";
    block += "import java.io.BufferedReader;\n";
    block += "import java.io.File;\n";
    block += "import java.io.FileInputStream;\n";
    block += "import java.io.FileNotFoundException;\n";
    block += "import java.io.IOException;\n";
    block += "import java.io.InputStreamReader;\n";
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "public class Analizador {\n";
    block += "    private final int ARQUITECTURA_8BITS = 8;\n";
    block += "    private final int ARQUITECTURA_16BITS = 16;\n";
    block += "    private final int ARQUITECTURA_32BITS = 32;\n";
    block += "    private final int TAM_PILA = 65535;\n";
    block += "    private Memoria[] memoria;\n";
    block += "    int modelo;\n";
    block += "    int tam_modelo = 65536; // Se establece por defecto tama;o de programa small\n";
    block += "    int[] registros = new int[8];\n";
    block += "    int programLength = 0;\n";
    block += "    int pc = 0;\n";
    block += "    int sp = 0;\n";
    block += "    int ds = 0;\n";
    block += "    boolean zf = false; // Flag de estado de cero, modificado despues de comparar dos numeros con CMP\n";
    block += "    boolean cf = false; // Flag de suma o resta, modificado despues de hacer una operacion de suma o resta\n";
    block += "    boolean bmModelo = false;\n";
    block += "    boolean bmDataSegment = false;\n";
    block += "    boolean bmCodeSegment = false;\n";
    block += "    void ObtenerModelo() {\n";
    block += "    }\n";
    block += "    enum eTipoOperando {\n";
    block += "        TO_REGISTRO_REGISTRO,\n";
    block += "        TO_REGISTRO_INMEDIATO,\n";
    block += "        TO_INMEDIATO_REGISTRO,\n";
    block += "        TO_REGISTRO_MEMORIA,\n";
    block += "        TO_MEMORIA_REGISTRO,\n";
    block += "        TO_INMEDIATO_INMEDIATO,\n";
    block += "        TO_REGISTRO,\n";
    block += "        TO_MEMORIA,\n";
    block += "        TO_INMEDIATO\n";
    block += "    };\n";
    block += "\n";
    block += "    enum eTipoOperacion {\n";
    block += "        OPERACION_SUMA,\n";
    block += "        OPERACION_RESTA,\n";
    block += "        OPERACION_DIVISION,\n";
    block += "        OPERACION_MULIPLICACION\n";
    block += "    };\n";
    block += "\n";
    block += "    enum eCantidadOperandos {\n";
    block += "        CO_UN_OPERANDO,\n";
    block += "        CO_DOS_OPERANDO,\n";
    block += "        CO_NINGUN_OPERANDO\n";
    block += "    };\n";
    block += "\n";
    block += "    enum eTipoError {\n";
    block += "        TE_TODO_BIEN,\n";
    block += "        TE_OPERANDO_DESTINO_NO_INMEDIATO,\n";
    block += "        TE_OPERANDO_DESTINO_NO_REGISTRO,\n";
    block += "        TE_OPERANDO_DESTINO_NO_MEMORIA,\n";
    block += "        TE_OPERANDO_ORIGEN_NO_INMEDIATO,\n";
    block += "        TE_OPERANDO_ORIGEN_NO_REGISTRO,\n";
    block += "        TE_OPERANDO_ORIGEN_NO_MEMORIA\n";
    block += "    };\n";
    block += "    File pArchivoEntrada, pArchivoSalida;\n";
    block += "    eTipoOperando emTipoOperando;\n";
    block += "    eTipoOperacion emTipoOperacion;\n";
    block += "    eInsrucciones emInstruccion;\n";
    block += "    eTipoError emTipoError;\n";
    block += "    int imValOrigen = 0, imValDestino = 0, imNumeroLinea;\n";
    block += "\n";
    block += "    public void main(String argv[]) throws FileNotFoundException, IOException {\n";
    block += "\n";
    block += "\n";
    block += "    }\n";
    block += "\n";
    block += "}\n";
    headerFile.write(block);
    headerFile.close();
}
void ClassWizard::GenerarArchivoPom(QString outputDir) {
    QByteArray block;
    QFile headerFile(QString("%1/%2").arg(outputDir).arg(smNombreArchivo) + "/" + "pom" + ".xml");
    block += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    block += "<project xmlns=\"http://maven.apache.org/POM/4.0.0\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd\">\n";
    block += "    <modelVersion>4.0.0</modelVersion>\n";
    block += "    <groupId>org</groupId>\n";
    block += QString("    <artifactId>%1</artifactId>\n").arg(smNombreArchivo);
    block += "    <version>1.0-SNAPSHOT</version>\n";
    block += "    <packaging>jar</packaging>\n";
    block += "    <properties>\n";
    block += "        <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>\n";
    block += "        <maven.compiler.source>1.8</maven.compiler.source>\n";
    block += "        <maven.compiler.target>1.8</maven.compiler.target>\n";
    block += "    </properties>\n";
    block += "</project>\n";
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    headerFile.write(block);
    headerFile.close();
}
void ClassWizard::GenerarMemoriaNetBeans(QString outputDir) {
    QByteArray block;
    QString slPackageName = "org";
    QFile headerFile(outputDir + "/" + "Memoria" + ".java");
    block += "/*\n";
    block += "* *********************************************************************************\n";
    block += "* ***                                                                           ***\n";
    block += "* *** Programa que emula memoria y conjunto de instrucciones de dos direcciones ***\n";
    block += "* *** Plantilla Generada por Ocamm                                              ***\n";
    block += "* *** Integrantes                                                               ***\n";
    block += "* *** Jorge Manuel Potosme Alvarez                                              ***\n";
    block += "* *** Harvin Manuel Toledo Polanco                                              ***\n";
    block += "* *** Domingo 7 de febrero de 2016                                              ***\n";
    block += "* ***                                                                           ***\n";
    block += "* *********************************************************************************\n";
    block += "* */\n";
    block += "package " + slPackageName + "." + smNombreArchivo + ";\n";
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "public class Memoria {\n";
    block += "    private int indice;\n";
    block += "    private int contenido;\n";
    block += "\n";
    block += "\n";
    block += "    public int getIndice() {\n";
    block += "        return indice;\n";
    block += "    }\n";
    block += "\n";
    block += "    public void setIndice(int indice) {\n";
    block += "        this.indice = indice;\n";
    block += "    }\n";
    block += "\n";
    block += "    public int getContenido() {\n";
    block += "        return contenido;\n";
    block += "    }\n";
    block += "\n";
    block += "    public void setContenido(int contenido) {\n";
    block += "        this.contenido = contenido;\n";
    block += "    }\n";
    block += "\n";
    block += "}\n";
    headerFile.write(block);
    headerFile.close();
}

void ClassWizard::GenerarMainNetBeans(QString outputDir) {
    QByteArray block;
    QString slPackageName = "org";
    QFile headerFile(outputDir + "/" + "main" + ".java");
    block += "/*\n";
    block += "* *********************************************************************************\n";
    block += "* ***                                                                           ***\n";
    block += "* *** Programa que emula memoria y conjunto de instrucciones de dos direcciones ***\n";
    block += "* *** Plantilla Generada por Ocamm                                              ***\n";
    block += "* *** Integrantes                                                               ***\n";
    block += "* *** Jorge Manuel Potosme Alvarez                                              ***\n";
    block += "* *** Harvin Manuel Toledo Polanco                                              ***\n";
    block += "* *** Domingo 7 de febrero de 2016                                              ***\n";
    block += "* ***                                                                           ***\n";
    block += "* *********************************************************************************\n";
    block += "* */\n";
    block += "package " + slPackageName + "." + smNombreArchivo + ";\n";
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "import java.io.IOException;\n";
    block += "import java.util.logging.Level;\n";
    block += "import java.util.logging.Logger;\n";

    block += "public class main {\n";
    block += "    public static void main(String argvs[]) {\n";
    block += "    Analizador a = new Analizador();\n";
    block += "    \n";
    block += "        try {\n";
    block += "            a.main(argvs);\n";
    block += "        } catch (IOException ex) {\n";
    block += "            Logger.getLogger(main.class.getName()).log(Level.SEVERE, null, ex);\n";
    block += "        }\n";
    block += "    }\n";
    block += "}\n";

    headerFile.write(block);
    headerFile.close();
}

void ClassWizard::GenerarCLSAnalizadorCSharp(QString outputDir) {
    QByteArray block;
    QFile headerFile(outputDir + "/" + "CLSAnalizador" + ".cs");
    block += "/*\n";
    block += "* *********************************************************************************\n";
    block += "* ***                                                                           ***\n";
    block += "* *** Programa que emula memoria y conjunto de instrucciones de dos direcciones ***\n";
    block += "* *** Plantilla Generada por Ocamm                                              ***\n";
    block += "* *** Integrantes                                                               ***\n";
    block += "* *** Jorge Manuel Potosme Alvarez                                              ***\n";
    block += "* *** Harvin Manuel Toledo Polanco                                              ***\n";
    block += "* *** Domingo 7 de febrero de 2016                                              ***\n";
    block += "* ***                                                                           ***\n";
    block += "* *********************************************************************************\n";
    block += "* */\n";
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "using System;\n";
    block += "using System.IO;\n";
    block += "\n";
    block += QString("namespace %1CS.%1\n").arg(smNombreArchivo);
    block += "{\n";
    block += "\n";
    block += "    class CLSAnalizador\n";
    block += "    {\n";
    block += "        private int ARQUITECTURA_8BITS = 8;\n";
    block += "        private int ARQUITECTURA_16BITS = 16;\n";
    block += "        private int ARQUITECTURA_32BITS = 32;\n";
    block += "        private int TAM_PILA = 65535;\n";
    block += "        private CLSMemoria[] memoria;\n";
    block += "        int modelo;\n";
    block += "        int tam_modelo = 65536; // Se establece por defecto tama;o de programa small\n";
    block += "        int[] registros = new int[8];\n";
    block += "        int programLength = 0;\n";
    block += "        int pc = 0;\n";
    block += "        int sp = 0;\n";
    block += "        int ds = 0;\n";
    block += "        bool zf = false; // Flag de estado de cero, modificado despues de comparar dos numeros con CMP\n";
    block += "        bool cf = false; // Flag de suma o resta, modificado despues de hacer una operacion de suma o resta\n";
    block += "        bool bmModelo = false;\n";
    block += "        bool bmDataSegment = false;\n";
    block += "        bool bmCodeSegment = false;\n";
    block += "\n";
    block += "        enum eInsrucciones\n";
    block += "        {\n";
    block += "            MOV,\n";
    block += "            ADD,\n";
    block += "            SUB,\n";
    block += "            MUL,\n";
    block += "            DIV,\n";
    block += "            AND,\n";
    block += "            OR,\n";
    block += "            XOR,\n";
    block += "            XNOR,\n";
    block += "            INC,\n";
    block += "            DEC,\n";
    block += "            INT,\n";
    block += "            PUSH,\n";
    block += "            POP,\n";
    block += "            JMP,\n";
    block += "            JMPZ,\n";
    block += "            JMPNZ,\n";
    block += "            CMP\n";
    block += "        };\n";
    block += "\n";
    block += "        enum eTipoOperando\n";
    block += "        {\n";
    block += "            TO_REGISTRO_REGISTRO,\n";
    block += "            TO_REGISTRO_INMEDIATO,\n";
    block += "            TO_INMEDIATO_REGISTRO,\n";
    block += "            TO_REGISTRO_MEMORIA,\n";
    block += "            TO_MEMORIA_REGISTRO,\n";
    block += "            TO_INMEDIATO_INMEDIATO,\n";
    block += "            TO_REGISTRO,\n";
    block += "            TO_MEMORIA,\n";
    block += "            TO_INMEDIATO\n";
    block += "        };\n";
    block += "\n";
    block += "        enum eTipoOperacion\n";
    block += "        {\n";
    block += "            OPERACION_SUMA,\n";
    block += "            OPERACION_RESTA,\n";
    block += "            OPERACION_DIVISION,\n";
    block += "            OPERACION_MULIPLICACION\n";
    block += "        };\n";
    block += "\n";
    block += "        enum eCantidadOperandos\n";
    block += "        {\n";
    block += "            CO_UN_OPERANDO,\n";
    block += "            CO_DOS_OPERANDO,\n";
    block += "            CO_NINGUN_OPERANDO\n";
    block += "        };\n";
    block += "\n";
    block += "        enum eTipoError\n";
    block += "        {\n";
    block += "            TE_TODO_BIEN,\n";
    block += "            TE_OPERANDO_DESTINO_NO_INMEDIATO,\n";
    block += "            TE_OPERANDO_DESTINO_NO_REGISTRO,\n";
    block += "            TE_OPERANDO_DESTINO_NO_MEMORIA,\n";
    block += "            TE_OPERANDO_ORIGEN_NO_INMEDIATO,\n";
    block += "            TE_OPERANDO_ORIGEN_NO_REGISTRO,\n";
    block += "            TE_OPERANDO_ORIGEN_NO_MEMORIA\n";
    block += "        };\n";
    block += "        string[] pArchivoEntrada, pArchivoSalida;\n";
    block += "        eTipoOperando emTipoOperando;\n";
    block += "        eTipoOperacion emTipoOperacion;\n";
    block += "        eInsrucciones emInstruccion;\n";
    block += "        eTipoError emTipoError;\n";
    block += "        int imValOrigen = 0, imValDestino = 0, imNumeroLinea;\n";
    block += "\n";
    block += "        public void main() {\n";
    block += "        }\n";
    block += "    }\n";
    block += "}\n";
    headerFile.write(block);
    headerFile.close();
}

void ClassWizard::GenerarCLSMemoriaCSharp(QString outputDir) {
    QByteArray block;
    QFile headerFile(outputDir + "/" + "CLSMemoria" + ".cs");
    block += "/*\n";
    block += "* *********************************************************************************\n";
    block += "* ***                                                                           ***\n";
    block += "* *** Programa que emula memoria y conjunto de instrucciones de dos direcciones ***\n";
    block += "* *** Plantilla Generada por Ocamm                                              ***\n";
    block += "* *** Integrantes                                                               ***\n";
    block += "* *** Jorge Manuel Potosme Alvarez                                              ***\n";
    block += "* *** Harvin Manuel Toledo Polanco                                              ***\n";
    block += "* *** Domingo 7 de febrero de 2016                                              ***\n";
    block += "* ***                                                                           ***\n";
    block += "* *********************************************************************************\n";
    block += "* */\n";
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "using System;\n";
    block += "using System.Collections.Generic;\n";
    block += "using System.Linq;\n";
    block += "using System.Text;\n";
    block += "using System.Threading.Tasks;\n";
    block += "\n";
    block += QString("namespace %1CS.%1\n").arg(smNombreArchivo);
    block += "{\n";
    block += "\n";
    block += "    class CLSMemoria\n";
    block += "    {\n";
    block += "        private int indice;\n";
    block += "       private int contenido;\n";
    block += "        public int getIndice()\n";
    block += "        {\n";
    block += "            return indice;\n";
    block += "        }\n";
    block += "\n";
    block += "        public void setIndice(int indice)\n";
    block += "        {\n";
    block += "            this.indice = indice;\n";
    block += "        }\n";
    block += "\n";
    block += "        public int getContenido()\n";
    block += "        {\n";
    block += "            return contenido;\n";
    block += "        }\n";
    block += "\n";
    block += "        public void setContenido(int contenido)\n";
    block += "        {\n";
    block += "            this.contenido = contenido;\n";
    block += "\n";
    block += "        }\n";
    block += "    }\n";
    block += "}\n";
    headerFile.write(block);
    headerFile.close();
}

void ClassWizard::GenerarPlantillaDeProyectoCSharp(QString outputDir) {
    QByteArray block;
    QFile headerFile(outputDir + "/" + smNombreArchivo + "CS" + ".csproj");
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    block += "<Project ToolsVersion=\"14.0\" DefaultTargets=\"Build\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">\n";
    block += "  <Import Project=\"$(MSBuildExtensionsPath)\\$(MSBuildToolsVersion)\\Microsoft.Common.props\" Condition=\"Exists('$(MSBuildExtensionsPath)\\$(MSBuildToolsVersion)\\Microsoft.Common.props')\" />\n";
    block += "  <PropertyGroup>\n";
    block += "    <Configuration Condition=\" '$(Configuration)' == '' \">Debug</Configuration>\n";
    block += "    <Platform Condition=\" '$(Platform)' == '' \">AnyCPU</Platform>\n";
    block += "    <ProjectGuid>{6C17A156-5A9E-4D69-B88C-E93735E56A3E}</ProjectGuid>\n";
    block += "    <OutputType>WinExe</OutputType>\n";
    block += "    <AppDesignerFolder>Properties</AppDesignerFolder>\n";
    block += "    <RootNamespace>" + smNombreArchivo + "CS" + "</RootNamespace>\n";
    block += "    <AssemblyName>" + smNombreArchivo + "CS" + "</AssemblyName>\n";
    block += "    <TargetFrameworkVersion>v4.5.2</TargetFrameworkVersion>\n";
    block += "    <FileAlignment>512</FileAlignment>\n";
    block += "    <AutoGenerateBindingRedirects>true</AutoGenerateBindingRedirects>\n";
    block += "  </PropertyGroup>\n";
    block += "  <PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Debug|AnyCPU' \">\n";
    block += "    <PlatformTarget>AnyCPU</PlatformTarget>\n";
    block += "    <DebugSymbols>true</DebugSymbols>\n";
    block += "    <DebugType>full</DebugType>\n";
    block += "    <Optimize>false</Optimize>\n";
    block += "    <OutputPath>bin\\Debug\\</OutputPath>\n";
    block += "    <DefineConstants>DEBUG;TRACE</DefineConstants>\n";
    block += "    <ErrorReport>prompt</ErrorReport>\n";
    block += "    <WarningLevel>4</WarningLevel>\n";
    block += "  </PropertyGroup>\n";
    block += "  <PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Release|AnyCPU' \">\n";
    block += "    <PlatformTarget>AnyCPU</PlatformTarget>\n";
    block += "    <DebugType>pdbonly</DebugType>\n";
    block += "    <Optimize>true</Optimize>\n";
    block += "    <OutputPath>bin\\Release\\</OutputPath>\n";
    block += "    <DefineConstants>TRACE</DefineConstants>\n";
    block += "    <ErrorReport>prompt</ErrorReport>\n";
    block += "    <WarningLevel>4</WarningLevel>\n";
    block += "  </PropertyGroup>\n";
    block += "  <ItemGroup>\n";
    block += "    <Reference Include=\"System\" />\n";
    block += "    <Reference Include=\"System.Core\" />\n";
    block += "    <Reference Include=\"System.Xml.Linq\" />\n";
    block += "    <Reference Include=\"System.Data.DataSetExtensions\" />\n";
    block += "    <Reference Include=\"Microsoft.CSharp\" />\n";
    block += "    <Reference Include=\"System.Data\" />\n";
    block += "    <Reference Include=\"System.Deployment\" />\n";
    block += "    <Reference Include=\"System.Drawing\" />\n";
    block += "    <Reference Include=\"System.Net.Http\" />\n";
    block += "    <Reference Include=\"System.Windows.Forms\" />\n";
    block += "    <Reference Include=\"System.Xml\" />\n";
    block += "  </ItemGroup>\n";
    block += "  <ItemGroup>\n";
    block += "    <Compile Include=\"Form1.cs\">\n";
    block += "      <SubType>Form</SubType>\n";
    block += "    </Compile>\n";
    block += "    <Compile Include=\"Form1.Designer.cs\">\n";
    block += "      <DependentUpon>Form1.cs</DependentUpon>\n";
    block += "    </Compile>\n";
    block += "    <Compile Include=\"Program.cs\" />\n";
    block += "    <Compile Include=\"Properties\\AssemblyInfo.cs\" />\n";
    block += "    <Compile Include=\"" + smNombreArchivo + "\\CLSAnalizador.cs\" />\n";
    block += "    <Compile Include=\"" + smNombreArchivo + "\\CLSMemoria.cs\" />\n";
    block += "    <EmbeddedResource Include=\"Properties\\Resources.resx\">\n";
    block += "      <Generator>ResXFileCodeGenerator</Generator>\n";
    block += "      <LastGenOutput>Resources.Designer.cs</LastGenOutput>\n";
    block += "      <SubType>Designer</SubType>\n";
    block += "    </EmbeddedResource>\n";
    block += "    <Compile Include=\"Properties\\Resources.Designer.cs\">\n";
    block += "      <AutoGen>True</AutoGen>\n";
    block += "      <DependentUpon>Resources.resx</DependentUpon>\n";
    block += "    </Compile>\n";
    block += "    <None Include=\"Properties\\Settings.settings\">\n";
    block += "      <Generator>SettingsSingleFileGenerator</Generator>\n";
    block += "      <LastGenOutput>Settings.Designer.cs</LastGenOutput>\n";
    block += "    </None>\n";
    block += "    <Compile Include=\"Properties\\Settings.Designer.cs\">\n";
    block += "      <AutoGen>True</AutoGen>\n";
    block += "      <DependentUpon>Settings.settings</DependentUpon>\n";
    block += "      <DesignTimeSharedInput>True</DesignTimeSharedInput>\n";
    block += "    </Compile>\n";
    block += "  </ItemGroup>\n";
    block += "  <ItemGroup>\n";
    block += "    <None Include=\"App.config\" />\n";
    block += "  </ItemGroup>\n";
    block += "  <Import Project=\"$(MSBuildToolsPath)\\Microsoft.CSharp.targets\" />\n";
    block += "  <!-- To modify your build process, add your task inside one of the targets below and uncomment it. \n";
    block += "       Other similar extension points exist, see Microsoft.Common.targets.\n";
    block += "  <Target Name=\"BeforeBuild\">\n";
    block += "  </Target>\n";
    block += "  <Target Name=\"AfterBuild\">\n";
    block += "  </Target>\n";
    block += "  -->\n";
    block += "</Project>\n";
    headerFile.write(block);
    headerFile.close();
}


void ClassWizard::GenerarArchivoProgramCSharp(QString outputDir) {
    QByteArray block;
    QFile headerFile(outputDir + "/" + "Program" + ".cs");
    block += "/*\n";
    block += "* *********************************************************************************\n";
    block += "* ***                                                                           ***\n";
    block += "* *** Programa que emula memoria y conjunto de instrucciones de dos direcciones ***\n";
    block += "* *** Plantilla Generada por Ocamm                                              ***\n";
    block += "* *** Integrantes                                                               ***\n";
    block += "* *** Jorge Manuel Potosme Alvarez                                              ***\n";
    block += "* *** Harvin Manuel Toledo Polanco                                              ***\n";
    block += "* *** Domingo 7 de febrero de 2016                                              ***\n";
    block += "* ***                                                                           ***\n";
    block += "* *********************************************************************************\n";
    block += "* */\n";
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "using System;\n";
    block += "using System.Collections.Generic;\n";
    block += "using System.Linq;\n";
    block += "using System.Threading.Tasks;\n";
    block += "using System.Windows.Forms;\n";
    block += "using " + smNombreArchivo + "CS" + "." + smNombreArchivo + ";\n";
    block += "\n";
    block += "namespace " + smNombreArchivo + "CS" + "\n";
    block += "{\n";
    block += "    static class Program\n";
    block += "    {\n";
    block += "        /// <summary>\n";
    block += "        /// The main entry point for the application.\n";
    block += "        /// </summary>\n";
    block += "        [STAThread]\n";
    block += "        static void Main()\n";
    block += "        {\n";
    block += "            /*Application.EnableVisualStyles();\n";
    block += "            Application.SetCompatibleTextRenderingDefault(false);\n";
    block += "            Application.Run(new Form1());*/\n";
    block += "            CLSAnalizador a = new CLSAnalizador();\n";
    block += "\n";
    block += "            a.main();\n";
    block += "        }\n";
    block += "\n";
    block += "     }\n";
    block += "}\n";
    headerFile.write(block);
    headerFile.close();
}
void ClassWizard::GenerarArchivoAppConfigCSharp(QString outputDir) {
    QByteArray block;
    QFile headerFile(outputDir + "/" + "App" + ".config");
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n";
    block += "<configuration>\n";
    block += "    <startup> \n";
    block += "        <supportedRuntime version=\"v4.0\" sku=\".NETFramework,Version=v4.5.2\" />\n";
    block += "    </startup>\n";
    block += "</configuration>\n";

    headerFile.write(block);
    headerFile.close();
}

void ClassWizard::GenerarArchivoForm1CSharp(QString outputDir) {
    QByteArray block;
    QFile headerFile(outputDir + "/" + "Form1" + ".cs");
    block += "/*\n";
    block += "* *********************************************************************************\n";
    block += "* ***                                                                           ***\n";
    block += "* *** Programa que emula memoria y conjunto de instrucciones de dos direcciones ***\n";
    block += "* *** Plantilla Generada por Ocamm                                              ***\n";
    block += "* *** Integrantes                                                               ***\n";
    block += "* *** Jorge Manuel Potosme Alvarez                                              ***\n";
    block += "* *** Harvin Manuel Toledo Polanco                                              ***\n";
    block += "* *** Domingo 7 de febrero de 2016                                              ***\n";
    block += "* ***                                                                           ***\n";
    block += "* *********************************************************************************\n";
    block += "* */\n";
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "using System;\n";
    block += "using System.Collections.Generic;\n";
    block += "using System.ComponentModel;\n";
    block += "using System.Data;\n";
    block += "using System.Drawing;\n";
    block += "using System.Linq;\n";
    block += "using System.Text;\n";
    block += "using System.Threading.Tasks;\n";
    block += "using System.Windows.Forms;\n";
    block += "\n";
    block += "namespace " + smNombreArchivo + "CS" + "\n";
    block += "{\n";
    block += "    public partial class Form1 : Form\n";
    block += "    {\n";
    block += "        public Form1()\n";
    block += "        {\n";
    block += "            InitializeComponent();\n";
    block += "        }\n";
    block += "    }\n";
    block += "}\n";
    headerFile.write(block);
    headerFile.close();
}

void ClassWizard::GenerarArchivoForm1DesignerCSharp(QString outputDir) {
    QByteArray block;
    QFile headerFile(outputDir + "/" + "Form1.Designer" + ".cs");
    block += "/*\n";
    block += "* *********************************************************************************\n";
    block += "* ***                                                                           ***\n";
    block += "* *** Programa que emula memoria y conjunto de instrucciones de dos direcciones ***\n";
    block += "* *** Plantilla Generada por Ocamm                                              ***\n";
    block += "* *** Integrantes                                                               ***\n";
    block += "* *** Jorge Manuel Potosme Alvarez                                              ***\n";
    block += "* *** Harvin Manuel Toledo Polanco                                              ***\n";
    block += "* *** Domingo 7 de febrero de 2016                                              ***\n";
    block += "* ***                                                                           ***\n";
    block += "* *********************************************************************************\n";
    block += "* */\n";
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "namespace " + smNombreArchivo + "CS" + "\n";
    block += "{\n";
    block += "    partial class Form1\n";
    block += "    {\n";
    block += "        /// <summary>\n";
    block += "        /// </summary>\n";
    block += "        private System.ComponentModel.IContainer components = null;\n";
    block += "\n";
    block += "        /// <summary>\n";
    block += "        /// Clean up any resources being used.\n";
    block += "        /// </summary>\n";
    block += "        /// <param name=\"disposing\">true if managed resources should be disposed; otherwise, false.</param>\n";
    block += "        protected override void Dispose(bool disposing)\n";
    block += "        {\n";
    block += "            if (disposing && (components != null))\n";
    block += "            {\n";
    block += "                components.Dispose();\n";
    block += "            }\n";
    block += "            base.Dispose(disposing);\n";
    block += "        }\n";
    block += "\n";
    block += "        #region Windows Form Designer generated code\n";
    block += "\n";
    block += "        /// <summary>\n";
    block += "        /// Required method for Designer support - do not modify\n";
    block += "        /// the contents of this method with the code editor.\n";
    block += "        /// </summary>\n";
    block += "        private void InitializeComponent()\n";
    block += "        {\n";
    block += "            this.components = new System.ComponentModel.Container();\n";
    block += "            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;\n";
    block += "            this.Text = \"Form1\";\n";
    block += "        }\n";
    block += "\n";
    block += "        #endregion\n";
    block += "    }\n";
    block += "}\n";
    headerFile.write(block);
    headerFile.close();
}

void ClassWizard::GenerarArchivoAssemblyInfoEnPropertiesCSharp(QString outputDir) {
    QByteArray block;
    QFile headerFile(outputDir + "/" + "AssemblyInfo" + ".cs");
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "using System.Reflection;\n";
    block += "using System.Runtime.CompilerServices;\n";
    block += "using System.Runtime.InteropServices;\n";
    block += "\n";
    block += "// General Information about an assembly is controlled through the following \n";
    block += "// set of attributes. Change these attribute values to modify the information\n";
    block += "// associated with an assembly.\n";
    block += "[assembly: AssemblyTitle(\"" + smNombreArchivo + "CS" + "\")]\n";
    block += "[assembly: AssemblyDescription(\"\")]\n";
    block += "[assembly: AssemblyConfiguration(\"\")]\n";
    block += "[assembly: AssemblyCompany(\"Hewlett-Packard\")]\n";
    block += "[assembly: AssemblyProduct(\"" + smNombreArchivo + "CS" + "\")]\n";
    block += "[assembly: AssemblyCopyright(\"Copyright © Hewlett-Packard 2016\")]\n";
    block += "[assembly: AssemblyTrademark(\"\")]\n";
    block += "[assembly: AssemblyCulture(\"\")]\n";
    block += "\n";
    block += "// Setting ComVisible to false makes the types in this assembly not visible \n";
    block += "// to COM components.  If you need to access a type in this assembly from \n";
    block += "// COM, set the ComVisible attribute to true on that type.\n";
    block += "[assembly: ComVisible(false)]\n";
    block += "\n";
    block += "// The following GUID is for the ID of the typelib if this project is exposed to COM\n";
    block += "[assembly: Guid(\"6c17a156-5a9e-4d69-b88c-e93735e56a3e\")]\n";
    block += "\n";
    block += "// Version information for an assembly consists of the following four values:\n";
    block += "//\n";
    block += "//      Major Version\n";
    block += "//      Minor Version \n";
    block += "//      Build Number\n";
    block += "//      Revision\n";
    block += "//\n";
    block += "// You can specify all the values or you can default the Build and Revision Numbers \n";
    block += "// by using the '*' as shown below:\n";
    block += "// [assembly: AssemblyVersion(\"1.0.*\")]\n";
    block += "[assembly: AssemblyVersion(\"1.0.0.0\")]\n";
    block += "[assembly: AssemblyFileVersion(\"1.0.0.0\")]\n";

    headerFile.write(block);
    headerFile.close();
}


void ClassWizard::GenerarArchivoResourceDesignerEnPropertiesCSharp(QString outputDir) {
    QByteArray block;
    QFile headerFile(outputDir + "/" + "Resources.Designer" + ".cs");
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "//------------------------------------------------------------------------------\n";
    block += "// <auto-generated>\n";
    block += "//     This code was generated by a tool.\n";
    block += "//     Runtime Version:4.0.30319.42000\n";
    block += "//\n";
    block += "//     Changes to this file may cause incorrect behavior and will be lost if\n";
    block += "//     the code is regenerated.\n";
    block += "// </auto-generated>\n";
    block += "//------------------------------------------------------------------------------\n";
    block += "\n";
    block += "namespace " + smNombreArchivo + "CS" + ".Properties\n";
    block += "{\n";
    block += "\n";
    block += "\n";
    block += "    /// <summary>\n";
    block += "    ///   A strongly-typed resource class, for looking up localized strings, etc.\n";
    block += "    /// </summary>\n";
    block += "    // This class was auto-generated by the StronglyTypedResourceBuilder\n";
    block += "    // class via a tool like ResGen or Visual Studio.\n";
    block += "    // To add or remove a member, edit your .ResX file then rerun ResGen\n";
    block += "    // with the /str option, or rebuild your VS project.\n";
    block += "    [global::System.CodeDom.Compiler.GeneratedCodeAttribute(\"System.Resources.Tools.StronglyTypedResourceBuilder\", \"4.0.0.0\")]\n";
    block += "    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]\n";
    block += "    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]\n";
    block += "    internal class Resources\n";
    block += "    {\n";
    block += "\n";
    block += "        private static global::System.Resources.ResourceManager resourceMan;\n";
    block += "\n";
    block += "        private static global::System.Globalization.CultureInfo resourceCulture;\n";
    block += "\n";
    block += "        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute(\"Microsoft.Performance\", \"CA1811:AvoidUncalledPrivateCode\")]\n";
    block += "        internal Resources()\n";
    block += "        {\n";
    block += "       }\n";
    block += "\n";
    block += "        /// <summary>\n";
    block += "        ///   Returns the cached ResourceManager instance used by this class.\n";
    block += "        /// </summary>\n";
    block += "        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]\n";
    block += "        internal static global::System.Resources.ResourceManager ResourceManager\n";
    block += "        {\n";
    block += "            get\n";
    block += "            {\n";
    block += "                if ((resourceMan == null))\n";
    block += "                {\n";
    block += "                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager(\"TemplateCS.Properties.Resources\", typeof(Resources).Assembly);\n";
    block += "                    resourceMan = temp;\n";
    block += "                }\n";
    block += "                return resourceMan;\n";
    block += "            }\n";
    block += "        }\n";
    block += "\n";
    block += "        /// <summary>\n";
    block += "        ///   Overrides the current thread's CurrentUICulture property for all\n";
    block += "        ///   resource lookups using this strongly typed resource class.\n";
    block += "        /// </summary>\n";
    block += "        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]\n";
    block += "        internal static global::System.Globalization.CultureInfo Culture\n";
    block += "        {\n";
    block += "            get\n";
    block += "            {\n";
    block += "                return resourceCulture;\n";
    block += "            }\n";
    block += "            set\n";
    block += "            {\n";
    block += "                resourceCulture = value;\n";
    block += "            }\n";
    block += "        }\n";
    block += "    }\n";
    block += "}\n";

    headerFile.write(block);
    headerFile.close();
}


void ClassWizard::GenerarArchivoResourceResxEnPropertiesCSharp(QString outputDir) {
    QByteArray block;
    QFile headerFile(outputDir + "/" + "Resources" + ".resx");
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    block += "<root>\n";
    block += "  <!-- \n";
    block += "    Microsoft ResX Schema \n";
    block += "    \n";
    block += "    Version 2.0\n";
    block += "    \n";
    block += "    The primary goals of this format is to allow a simple XML format \n";
    block += "    that is mostly human readable. The generation and parsing of the \n";
    block += "    various data types are done through the TypeConverter classes \n";
    block += "    associated with the data types.\n";
    block += "    \n";
    block += "    Example:\n";
    block += "    \n";
    block += "    ... ado.net/XML headers & schema ...\n";
    block += "    <resheader name=\"resmimetype\">text/microsoft-resx</resheader>\n";
    block += "    <resheader name=\"version\">2.0</resheader>\n";
    block += "    <resheader name=\"reader\">System.Resources.ResXResourceReader, System.Windows.Forms, ...</resheader>\n";
    block += "    <resheader name=\"writer\">System.Resources.ResXResourceWriter, System.Windows.Forms, ...</resheader>\n";
    block += "    <data name=\"Name1\"><value>this is my long string</value><comment>this is a comment</comment></data>\n";
    block += "    <data name=\"Color1\" type=\"System.Drawing.Color, System.Drawing\">Blue</data>\n";
    block += "    <data name=\"Bitmap1\" mimetype=\"application/x-microsoft.net.object.binary.base64\">\n";
    block += "        <value>[base64 mime encoded serialized .NET Framework object]</value>\n";
    block += "    </data>\n";
    block += "    <data name=\"Icon1\" type=\"System.Drawing.Icon, System.Drawing\" mimetype=\"application/x-microsoft.net.object.bytearray.base64\">\n";
    block += "        <value>[base64 mime encoded string representing a byte array form of the .NET Framework object]</value>\n";
    block += "        <comment>This is a comment</comment>\n";
    block += "    </data>\n";
    block += "        \n";
    block += "    There are any number of \"resheader\" rows that contain simple \n";
    block += "    name/value pairs.\n";
    block += "    \n";
    block += "    Each data row contains a name, and value. The row also contains a \n";
    block += "    type or mimetype. Type corresponds to a .NET class that support \n";
    block += "    text/value conversion through the TypeConverter architecture. \n";
    block += "    Classes that don't support this are serialized and stored with the \n";
    block += "    mimetype set.\n";
    block += "    \n";
    block += "    The mimetype is used for serialized objects, and tells the \n";
    block += "    ResXResourceReader how to depersist the object. This is currently not \n";
    block += "    extensible. For a given mimetype the value must be set accordingly:\n";
    block += "    \n";
    block += "    Note - application/x-microsoft.net.object.binary.base64 is the format \n";
    block += "    that the ResXResourceWriter will generate, however the reader can \n";
    block += "    read any of the formats listed below.\n";
    block += "    \n";
    block += "    mimetype: application/x-microsoft.net.object.binary.base64\n";
    block += "    value   : The object must be serialized with \n";
    block += "            : System.Serialization.Formatters.Binary.BinaryFormatter\n";
    block += "            : and then encoded with base64 encoding.\n";
    block += "    \n";
    block += "    mimetype: application/x-microsoft.net.object.soap.base64\n";
    block += "    value   : The object must be serialized with \n";
    block += "            : System.Runtime.Serialization.Formatters.Soap.SoapFormatter\n";
    block += "            : and then encoded with base64 encoding.\n";
    block += "\n";
    block += "    mimetype: application/x-microsoft.net.object.bytearray.base64\n";
    block += "    value   : The object must be serialized into a byte array \n";
    block += "            : using a System.ComponentModel.TypeConverter\n";
    block += "            : and then encoded with base64 encoding.\n";
    block += "    -->\n";
    block += "  <xsd:schema id=\"root\" xmlns=\"\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:msdata=\"urn:schemas-microsoft-com:xml-msdata\">\n";
    block += "    <xsd:element name=\"root\" msdata:IsDataSet=\"true\">\n";
    block += "      <xsd:complexType>\n";
    block += "        <xsd:choice maxOccurs=\"unbounded\">\n";
    block += "          <xsd:element name=\"metadata\">\n";
    block += "            <xsd:complexType>\n";
    block += "              <xsd:sequence>\n";
    block += "                <xsd:element name=\"value\" type=\"xsd:string\" minOccurs=\"0\" />\n";
    block += "              </xsd:sequence>\n";
    block += "              <xsd:attribute name=\"name\" type=\"xsd:string\" />\n";
    block += "              <xsd:attribute name=\"type\" type=\"xsd:string\" />\n";
    block += "              <xsd:attribute name=\"mimetype\" type=\"xsd:string\" />\n";
    block += "            </xsd:complexType>\n";
    block += "          </xsd:element>\n";
    block += "          <xsd:element name=\"assembly\">\n";
    block += "            <xsd:complexType>\n";
    block += "              <xsd:attribute name=\"alias\" type=\"xsd:string\" />\n";
    block += "              <xsd:attribute name=\"name\" type=\"xsd:string\" />\n";
    block += "            </xsd:complexType>\n";
    block += "          </xsd:element>\n";
    block += "          <xsd:element name=\"data\">\n";
    block += "            <xsd:complexType>\n";
    block += "              <xsd:sequence>\n";
    block += "                <xsd:element name=\"value\" type=\"xsd:string\" minOccurs=\"0\" msdata:Ordinal=\"1\" />\n";
    block += "                <xsd:element name=\"comment\" type=\"xsd:string\" minOccurs=\"0\" msdata:Ordinal=\"2\" />\n";
    block += "              </xsd:sequence>\n";
    block += "              <xsd:attribute name=\"name\" type=\"xsd:string\" msdata:Ordinal=\"1\" />\n";
    block += "              <xsd:attribute name=\"type\" type=\"xsd:string\" msdata:Ordinal=\"3\" />\n";
    block += "              <xsd:attribute name=\"mimetype\" type=\"xsd:string\" msdata:Ordinal=\"4\" />\n";
    block += "            </xsd:complexType>\n";
    block += "          </xsd:element>\n";
    block += "          <xsd:element name=\"resheader\">\n";
    block += "            <xsd:complexType>\n";
    block += "              <xsd:sequence>\n";
    block += "                <xsd:element name=\"value\" type=\"xsd:string\" minOccurs=\"0\" msdata:Ordinal=\"1\" />\n";
    block += "              </xsd:sequence>\n";
    block += "              <xsd:attribute name=\"name\" type=\"xsd:string\" use=\"required\" />\n";
    block += "            </xsd:complexType>\n";
    block += "          </xsd:element>\n";
    block += "        </xsd:choice>\n";
    block += "      </xsd:complexType>\n";
    block += "    </xsd:element>\n";
    block += "  </xsd:schema>\n";
    block += "  <resheader name=\"resmimetype\">\n";
    block += "    <value>text/microsoft-resx</value>\n";
    block += "  </resheader>\n";
    block += "  <resheader name=\"version\">\n";
    block += "    <value>2.0</value>\n";
    block += "  </resheader>\n";
    block += "  <resheader name=\"reader\">\n";
    block += "    <value>System.Resources.ResXResourceReader, System.Windows.Forms, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089</value>\n";
    block += "  </resheader>\n";
    block += "  <resheader name=\"writer\">\n";
    block += "    <value>System.Resources.ResXResourceWriter, System.Windows.Forms, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089</value>\n";
    block += "  </resheader>\n";
    block += "</root>\n";
    headerFile.write(block);
    headerFile.close();
}

void ClassWizard::GenerarArchivoSettingsDesignerEnPropertiesCSharp(QString outputDir) {
    QByteArray block;
    QFile headerFile(outputDir + "/" + "Settings.Designer" + ".cs");
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "//------------------------------------------------------------------------------\n";
    block += "// <auto-generated>\n";
    block += "//     This code was generated by a tool.\n";
    block += "//     Runtime Version:4.0.30319.42000\n";
    block += "//\n";
    block += "//     Changes to this file may cause incorrect behavior and will be lost if\n";
    block += "//     the code is regenerated.\n";
    block += "// </auto-generated>\n";
    block += "//------------------------------------------------------------------------------\n";
    block += "\n";
    block += "namespace " + smNombreArchivo + "CS" + ".Properties\n";
    block += "{\n";
    block += "\n";
    block += "\n";
    block += "    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]\n";
    block += "    [global::System.CodeDom.Compiler.GeneratedCodeAttribute(\"Microsoft.VisualStudio.Editors.SettingsDesigner.SettingsSingleFileGenerator\", \"11.0.0.0\")]\n";
    block += "    internal sealed partial class Settings : global::System.Configuration.ApplicationSettingsBase\n";
    block += "    {\n";
    block += "\n";
    block += "        private static Settings defaultInstance = ((Settings)(global::System.Configuration.ApplicationSettingsBase.Synchronized(new Settings())));\n";
    block += "\n";
    block += "        public static Settings Default\n";
    block += "        {\n";
    block += "            get\n";
    block += "            {\n";
    block += "                return defaultInstance;\n";
    block += "            }\n";
    block += "        }\n";
    block += "    }\n";
    block += "}\n";
    headerFile.write(block);
    headerFile.close();
}

void ClassWizard::GenerarArchivoSettingsSettingsEnPropertiesCSharp(QString outputDir) {
    QByteArray block;
    QFile headerFile(outputDir + "/" + "Settings" + ".settings");
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "<?xml version='1.0' encoding='utf-8'?>\n";
    block += "<SettingsFile xmlns=\"http://schemas.microsoft.com/VisualStudio/2004/01/settings\" CurrentProfile=\"(Default)\">\n";
    block += "  <Profiles>\n";
    block += "    <Profile Name=\"(Default)\" />\n";
    block += "  </Profiles>\n";
    block += "  <Settings />\n";
    block += "</SettingsFile>\n";
    headerFile.write(block);
    headerFile.close();
}

void ClassWizard::GenerarArchivoDeSolucionDelProyectoCSharp(QString outputDir) {
    QByteArray block;
    QFile headerFile(outputDir + "/" + smNombreArchivo + "CS" + ".sln");
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Creacion de archivo java para Netbeans"),
        QObject::tr("No se pudo escrir el arcihvio %1:\n%2")
        .arg(headerFile.fileName())
        .arg(headerFile.errorString()));
        return;
    }
    block += "\n";
    block += "Microsoft Visual Studio Solution File, Format Version 12.00\n";
    block += "# Visual Studio 14\n";
    block += "VisualStudioVersion = 14.0.24720.0\n";
    block += "MinimumVisualStudioVersion = 10.0.40219.1\n";
    block += "Project(\"{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}\") = \"" + smNombreArchivo + "CS" + "\", \"" + smNombreArchivo + "CS" + "\\" + smNombreArchivo + "CS" + ".csproj\", \"{6C17A156-5A9E-4D69-B88C-E93735E56A3E}\"\n";
    block += "EndProject\n";
    block += "Global\n";
    block += "	GlobalSection(SolutionConfigurationPlatforms) = preSolution\n";
    block += "		Debug|Any CPU = Debug|Any CPU\n";
    block += "		Release|Any CPU = Release|Any CPU\n";
    block += "	EndGlobalSection\n";
    block += "	GlobalSection(ProjectConfigurationPlatforms) = postSolution\n";
    block += "		{6C17A156-5A9E-4D69-B88C-E93735E56A3E}.Debug|Any CPU.ActiveCfg = Debug|Any CPU\n";
    block += "		{6C17A156-5A9E-4D69-B88C-E93735E56A3E}.Debug|Any CPU.Build.0 = Debug|Any CPU\n";
    block += "		{6C17A156-5A9E-4D69-B88C-E93735E56A3E}.Release|Any CPU.ActiveCfg = Release|Any CPU\n";
    block += "		{6C17A156-5A9E-4D69-B88C-E93735E56A3E}.Release|Any CPU.Build.0 = Release|Any CPU\n";
    block += "	EndGlobalSection\n";
    block += "	GlobalSection(SolutionProperties) = preSolution\n";
    block += "		HideSolutionNode = FALSE\n";
    block += "	EndGlobalSection\n";
    block += "EndGlobal\n";


    headerFile.write(block);
    headerFile.close();
}


bool ClassWizard::AnalizarCodigo() {
    bool blResultado = false; // El resultado es verdadero si el codigo se compilo con exito
    // Verificar definiciones y arquitectura
    // Verificar nombre de proyecto
    // Verificar nombre de docente
    // Analizar cuerpo de codigo de definicion de programa
}
