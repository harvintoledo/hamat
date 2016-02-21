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
    smAsignaturaDefinida =
    smTemaDefinido = "";
}
void ClassWizard::accept() {
    //    QByteArray className = field("omEditNombreDelProyecto").toByteArray();
    smNombreDelProyecto = field("omEditNombreDelProyecto").toString();
    QString outputDir = field("omLineEditDirectorioDeUbicacionDelProyectoPorDefecto").toString();
    smUbicacionDelProyecto = outputDir;
    //    GeneraProyectoCompletoParaJavaMaven(outputDir);
    //    GeneraProyectoCompletoParaCSharp(outputDir);
    GenerarProyectoOccam(outputDir);
    QDialog::accept();
}
void ClassWizard::GenerarProyectoOccam(QString outputDir) {
    QByteArray block;
    QFile headerFile(outputDir + "/" + smNombreDelProyecto + ".occam");
    if(!field("omEditNombreDelProyecto").toByteArray().isEmpty()) {
        block += ".NOMBREPROYECTO\n";
        block += field("omEditNombreDelProyecto").toByteArray() + "\n";
    }
    block += ".FECHA\n";
    block += QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") + "\n";
    if (field("omRadioButtonNetbeans").toBool()) {
        block += ".PLATAFORMA\n";
        block += "JAVANEBEANSOECLIPSE\n";
    }
    else if (field("omRadioButtonCSharp").toBool()) {
        block += ".PLATAFORMA\n";
        block += "VISUALSTUDIOCSHARP\n";
    }
    if(!field("omLineEditNombreDocente").toByteArray().isEmpty()) {
        block += ".DOCENTE\n";
        block += field("omLineEditNombreDocente").toByteArray() + "\n";
    }
    if(!field("omLineEditNombreIntegrante1").toByteArray().isEmpty()) {
        block += ".INTEGRANTE\n";
        block += field("omLineEditNombreIntegrante1").toByteArray() + "\n";
    }
    if(!field("omLineEditNombreIntegrante2").toByteArray().isEmpty()) {
        block += ".INTEGRANTE\n";
        block += field("omLineEditNombreIntegrante2").toByteArray() + "\n";
    }
    if(!field("omLineEditNombreIntegrante3").toByteArray().isEmpty()) {
        block += ".INTEGRANTE\n";
        block += field("omLineEditNombreIntegrante3").toByteArray() + "\n";
    }
    if(!field("omLineEditNombreIntegrante4").toByteArray().isEmpty()) {
        block += ".INTEGRANTE\n";
        block += field("omLineEditNombreIntegrante4").toByteArray() + "\n";
    }
    if(!field("omLineEditNombreIntegrante5").toByteArray().isEmpty()) {
        block += ".INTEGRANTE\n";
        block += field("omLineEditNombreIntegrante5").toByteArray() + "\n";
    }
    if(!field("omLineEditNombreIntegrante6").toByteArray().isEmpty()) {
        block += ".INTEGRANTE\n";
        block += field("omLineEditNombreIntegrante6").toByteArray() + "\n";
    }
    if (field("omRadioButtonArquitectura2Direcciones").toBool()) {
        block += ".ARQUITECTURA\n";
        block += "DOSDIRECCIONES\n";
    }
    else if (field("omRadioButtonArquitectura3Direcciones").toBool()) {
        block += ".ARQUITECTURA\n";
        block += "TRESDIRECCIONES\n";
    }
    else if (field("omRadioButtonArquitecturaPila").toBool()) {
        block += ".ARQUITECTURA\n";
        block += "PILA\n";
    }
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
void ClassWizard::GeneraProyectoCompletoParaCSharp(QString outputDir){
    bool blResultadoCreacionDeDirectorio = false;
    QDir olDirectorioProyecto(QString("%1/%2").arg(outputDir).arg(smNombreDelProyecto));
    // Crear directorio donde estan los archivos principales de ensamblador
    if(!olDirectorioProyecto.exists()) {
        if(olDirectorioProyecto.mkdir(QString("%1/%2CS").arg(outputDir).arg(smNombreDelProyecto))) {
            olDirectorioProyecto.setPath(QString("%1/%2CS/%2CS")
            .arg(outputDir)
            .arg(smNombreDelProyecto));
            if(!olDirectorioProyecto.exists()) {
                if(olDirectorioProyecto.mkdir(QString("%1/%2CS/%2CS")
                            .arg(outputDir)
                            .arg(smNombreDelProyecto))) {
                    olDirectorioProyecto.setPath(QString("%1/%2CS/%2CS/%2")
                    .arg(outputDir)
                    .arg(smNombreDelProyecto));
                    if(!olDirectorioProyecto.exists()) {
                        if(olDirectorioProyecto.mkdir(QString("%1/%2CS/%2CS/%2")
                                    .arg(outputDir)
                                    .arg(smNombreDelProyecto)))
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
    .arg(smNombreDelProyecto));
    GenerarPlantillaDeProyectoCSharp(olDirectorioProyecto.absolutePath());
    GenerarArchivoProgramCSharp(olDirectorioProyecto.absolutePath());
    GenerarArchivoAppConfigCSharp(olDirectorioProyecto.absolutePath());
    GenerarArchivoForm1CSharp(olDirectorioProyecto.absolutePath());
    GenerarArchivoForm1DesignerCSharp(olDirectorioProyecto.absolutePath());
    olDirectorioProyecto.setPath(QString("%1/%2CS/%2CS/Properties")
    .arg(outputDir)
    .arg(smNombreDelProyecto));
    if(!olDirectorioProyecto.exists()) {
        if(olDirectorioProyecto.mkdir(QString("%1/%2CS/%2CS/Properties")
                    .arg(outputDir)
                    .arg(smNombreDelProyecto))) {
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
    .arg(smNombreDelProyecto));
    GenerarArchivoDeSolucionDelProyectoCSharp(olDirectorioProyecto.absolutePath());
}
void ClassWizard::GeneraProyectoCompletoParaJavaMaven(QString outputDir){
    bool blResultadoCreacionDeDirectorio = false;
    QDir olDirectorioProyecto(QString("%1/%2").arg(outputDir).arg(smNombreDelProyecto));
    if(!olDirectorioProyecto.exists()) {
        if(olDirectorioProyecto.mkdir(QString("%1/%2").arg(outputDir).arg(smNombreDelProyecto))) {
            olDirectorioProyecto.setPath(QString("%1/%2/src").arg(outputDir).arg(smNombreDelProyecto));
            if(!olDirectorioProyecto.exists()) {
                if(olDirectorioProyecto.mkdir(QString("%1/%2/src").arg(outputDir).arg(smNombreDelProyecto))) {
                    olDirectorioProyecto.setPath(QString("%1/%2/src/main").arg(outputDir).arg(smNombreDelProyecto));
                    if(!olDirectorioProyecto.exists()) {
                        if(olDirectorioProyecto.mkdir(QString("%1/%2/src/main").arg(outputDir).arg(smNombreDelProyecto))) {
                            olDirectorioProyecto.setPath(QString("%1/%2/src/main/java").arg(outputDir).arg(smNombreDelProyecto));
                            if(!olDirectorioProyecto.exists()) {
                                if(olDirectorioProyecto.mkdir(QString("%1/%2/src/main/java").arg(outputDir).arg(smNombreDelProyecto))) {
                                    olDirectorioProyecto.setPath(QString("%1/%2/src/main/java/org").arg(outputDir).arg(smNombreDelProyecto));
                                    if(!olDirectorioProyecto.exists()) {
                                        if(olDirectorioProyecto.mkdir(QString("%1/%2/src/main/java/org").arg(outputDir).arg(smNombreDelProyecto))) {
                                            olDirectorioProyecto.setPath(QString("%1/%2/src/main/java/org/%3").arg(outputDir).arg(smNombreDelProyecto).arg(smNombreDelProyecto.toLower()));
                                            if(!olDirectorioProyecto.exists()) {
                                                if(olDirectorioProyecto.mkdir(QString("%1/%2/src/main/java/org/%3").arg(outputDir).arg(smNombreDelProyecto).arg(smNombreDelProyecto.toLower())))
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
    block += "package " + slPackageName + "." + smNombreDelProyecto + ";\n";
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
    QFile headerFile(QString("%1/%2").arg(outputDir).arg(smNombreDelProyecto) + "/" + "pom" + ".xml");
    block += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    block += "<project xmlns=\"http://maven.apache.org/POM/4.0.0\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd\">\n";
    block += "    <modelVersion>4.0.0</modelVersion>\n";
    block += "    <groupId>org</groupId>\n";
    block += QString("    <artifactId>%1</artifactId>\n").arg(smNombreDelProyecto);
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
    block += "package " + slPackageName + "." + smNombreDelProyecto + ";\n";
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
    block += "package " + slPackageName + "." + smNombreDelProyecto + ";\n";
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
    block += QString("namespace %1CS.%1\n").arg(smNombreDelProyecto);
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
    block += QString("namespace %1CS.%1\n").arg(smNombreDelProyecto);
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
    QFile headerFile(outputDir + "/" + smNombreDelProyecto + "CS" + ".csproj");
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
    block += "    <RootNamespace>" + smNombreDelProyecto + "CS" + "</RootNamespace>\n";
    block += "    <AssemblyName>" + smNombreDelProyecto + "CS" + "</AssemblyName>\n";
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
    block += "    <Compile Include=\"" + smNombreDelProyecto + "\\CLSAnalizador.cs\" />\n";
    block += "    <Compile Include=\"" + smNombreDelProyecto + "\\CLSMemoria.cs\" />\n";
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
    block += "using " + smNombreDelProyecto + "CS" + "." + smNombreDelProyecto + ";\n";
    block += "\n";
    block += "namespace " + smNombreDelProyecto + "CS" + "\n";
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
    block += "namespace " + smNombreDelProyecto + "CS" + "\n";
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
    block += "namespace " + smNombreDelProyecto + "CS" + "\n";
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
    block += "[assembly: AssemblyTitle(\"" + smNombreDelProyecto + "CS" + "\")]\n";
    block += "[assembly: AssemblyDescription(\"\")]\n";
    block += "[assembly: AssemblyConfiguration(\"\")]\n";
    block += "[assembly: AssemblyCompany(\"Hewlett-Packard\")]\n";
    block += "[assembly: AssemblyProduct(\"" + smNombreDelProyecto + "CS" + "\")]\n";
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
    block += "namespace " + smNombreDelProyecto + "CS" + ".Properties\n";
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
    block += "namespace " + smNombreDelProyecto + "CS" + ".Properties\n";
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
    QFile headerFile(outputDir + "/" + smNombreDelProyecto + "CS" + ".sln");
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
    block += "Project(\"{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}\") = \"" + smNombreDelProyecto + "CS" + "\", \"" + smNombreDelProyecto + "CS" + "\\" + smNombreDelProyecto + "CS" + ".csproj\", \"{6C17A156-5A9E-4D69-B88C-E93735E56A3E}\"\n";
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
