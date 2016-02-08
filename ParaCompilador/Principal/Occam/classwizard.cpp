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
        if(olDirectorioProyecto.mkdir(QString("%1/%2").arg(outputDir).arg(smNombreArchivo))) {
            olDirectorioProyecto.setPath(QString("%1/%2/%2CS")
                                         .arg(outputDir)
                                         .arg(smNombreArchivo));
            if(!olDirectorioProyecto.exists()) {
                if(olDirectorioProyecto.mkdir(QString("%1/%2/%3CS").arg(outputDir).arg(smNombreArchivo).arg(smNombreArchivo))) {
                    olDirectorioProyecto.setPath(QString("%1/%2/%2CS/%2")
                                                 .arg(outputDir)
                                                 .arg(smNombreArchivo));
                     if(!olDirectorioProyecto.exists()) {
                         if(olDirectorioProyecto.mkdir(QString("%1/%2/%2CS/%2")
                                 .arg(outputDir)
                                 .arg(smNombreArchivo)))
                             blResultadoCreacionDeDirectorio = true;
                     }

                }
            }
        }
    }
    GenerarCLSAnalizadorNetBeans(olDirectorioProyecto.absolutePath());
    GenerarCLSMemoriaNetBeans(olDirectorioProyecto.absolutePath());
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
    "la arquitectora para la que construira el simulador "
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

void ClassWizard::GenerarCLSAnalizadorNetBeans(QString outputDir) {
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

void ClassWizard::GenerarCLSMemoriaNetBeans(QString outputDir) {
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
