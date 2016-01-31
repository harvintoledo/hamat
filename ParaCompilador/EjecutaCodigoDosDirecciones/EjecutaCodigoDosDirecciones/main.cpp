/*
* *********************************************************************************
* ***                                                                           ***
* *** Programa que emula memoria y conjunto de instrucciones de dos direcciones ***
* *** Proyecto Final de Monografia Para Obtención de Título de Ingeniero        ***
* *** Autores                                                                   ***
* *** Jorge Manuel Potosme Alvarez                                              ***
* *** Harvin Manuel Toledo Polanco                                              ***
* *** Sabado 30 de enero de 2016                                                ***
* ***                                                                           ***
* *********************************************************************************
* */
#include <QCoreApplication>
#include <QString>
#include <QStringList>
#include <stdio.h>
typedef struct {
    int indice;
    int contenido;
} stMemoria;

stMemoria *memoria;
int modelo;
int tam_modelo = 65536; // Se establece por defecto tama;o de programa small
int registros[8];
int programLength = 0;
int pc = 0;
int sp = 0;
int ds = 0;
bool zf = false;
bool bmModelo = false;
bool bmDataSegment = false;
bool bmCodeSegment = false;
void ReservarMemoria();
void CargarMemoriaConIndiceYSinContenido();
void ObtenerModelo();
void EjecutarInstruccion(char *);
void Verificar1Operandos(QString);
void Verificar2Operandos(QString, QString);
void CompilarPrograma();
void EvaluarInstruccion();
enum eInsrucciones {
    MOV,
    ADD,
    SUB,
    MUL,
    DIV,
    INC,
    DEC,
    INT,
    JMP,
    JMPZ,
    JMPNZ,
    CMP,

};
enum eTipoOperando {
    TO_REGISTRO_REGISTRO,
    TO_REGISTRO_INMEDIATO,
    TO_INMEDIATO_REGISTRO,
    TO_REGISTRO_MEMORIA,
    TO_MEMORIA_REGISTRO,
    TO_INMEDIATO_INMEDIATO,
    TO_REGISTRO,
    TO_MEMORIA
};
enum eTipoOperacion {
    OPERACION_SUMA,
    OPERACION_RESTA,
    OPERACION_DIVISION,
    OPERACION_MULIPLICACION
};
enum eCantidadOperandos {
    CO_UN_OPERANDO,
    CO_DOS_OPERANDO,
    CO_NINGUN_OPERANDO
};
FILE *pArchivoEntrada, *pArchivoSalida;
eTipoOperando emTipoOperando;
eTipoOperacion emTipoOperacion;
eInsrucciones emInstruccion;
int imValOrigen = 0, imValDestino = 0, imNumeroLinea;
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    char caracteres[100];
    printf("Abriendo archivo con instrucciones");
    pArchivoEntrada = fopen("C:\\Users\\WESKER\\Documents\\QtProjects\\ControlDeVersiones\\ParaCompilador\\SalidasOcam\\prog.asm", "r");
    if (pArchivoEntrada == NULL) {
        fputs ("File error",stderr);
        exit (1);
    }
    printf("\nEl contenido del archivo de prueba es \n\n");
    ReservarMemoria();
    CargarMemoriaConIndiceYSinContenido();
    while (feof(pArchivoEntrada) == 0) {
        fgets(caracteres, 100, pArchivoEntrada);
        printf("%s", caracteres);
        EjecutarInstruccion(caracteres);
        system("PAUSE");
        imNumeroLinea ++;
    }
    system("PAUSE");
    fclose ( pArchivoEntrada );
    printf("Probando compilador qt para Windows.");
    getchar();
    return a.exec();
}
void ReservarMemoria() {
    memoria = new stMemoria[tam_modelo];
}

void CargarMemoriaConIndiceYSinContenido() {
    for(int i = 0; i < tam_modelo; i++) {
        memoria->contenido = 0;
        memoria->indice = i;
    }
}

void EjecutarInstruccion(char *instruccion) {
    QString slInstruccion = QString("%1").arg(instruccion);
    QString slInstruccionAEjecutar;
    slInstruccion = slInstruccion.toLower();
    slInstruccion = slInstruccion.simplified();
    if(slInstruccion.contains(QRegExp("^;\\b"))) {
        // Ignorar instruccion
        return;
    }
    else
    if(slInstruccion.contains(QRegExp("mov"))) {
        emInstruccion = MOV;
        printf("MOV\n");
        slInstruccionAEjecutar = slInstruccion.replace("mov", "");
        printf("slInstruccionAEjecutar\n");
        QStringList sllOperadorOperandos  = slInstruccionAEjecutar.split(",");
        QString slDestino, slOrigen;
        if(!sllOperadorOperandos.isEmpty()) {
            if(sllOperadorOperandos.length() != 2) {
                printf("Error diferente de dos operandos.\n");
                return;
            }
            else {
                slDestino = sllOperadorOperandos.first();
                slOrigen = sllOperadorOperandos.last();
                Verificar2Operandos(slDestino, slOrigen);
            }
        }
        else {
            printf("Error instruccion vacia.");
        }
    }
    else if(slInstruccion.contains(QRegExp("add"))) {
        emInstruccion = ADD;
        printf("ADD\n");
        slInstruccionAEjecutar = slInstruccion.replace("add", "");
        printf("slInstruccionAEjecutar\n");
        QStringList sllOperadorOperandos  = slInstruccionAEjecutar.split(",");
        QString slDestino, slOrigen;
        if(!sllOperadorOperandos.isEmpty()) {
            if(sllOperadorOperandos.length() != 2) {
                printf("Error diferente de dos operandos.\n");
                return;
            }
            else {
                slDestino = sllOperadorOperandos.first();
                slOrigen = sllOperadorOperandos.last();
                Verificar2Operandos(slDestino, slOrigen);
            }
        }
    }
    else if(slInstruccion.contains(QRegExp("sub"))) {
        emInstruccion = SUB;
        printf("SUB\n");
        slInstruccionAEjecutar = slInstruccion.replace("sub", "");
        printf("slInstruccionAEjecutar\n");
        QStringList sllOperadorOperandos  = slInstruccionAEjecutar.split(",");
        QString slDestino, slOrigen;
        if(!sllOperadorOperandos.isEmpty()) {
            if(sllOperadorOperandos.length() != 2) {
                printf("Error diferente de dos operandos.\n");
                return;
            }
            else {
                slDestino = sllOperadorOperandos.first();
                slOrigen = sllOperadorOperandos.last();
                Verificar2Operandos(slDestino, slOrigen);
            }
        }
    }
    else if(slInstruccion.contains(QRegExp("div"))) {
        emInstruccion = DIV;
        printf("DIV\n");
        slInstruccionAEjecutar = slInstruccion.replace("div", "");
        printf("slInstruccionAEjecutar\n");
        QStringList sllOperadorOperandos  = slInstruccionAEjecutar.split(",");
        QString slDestino, slOrigen;
        if(!sllOperadorOperandos.isEmpty()) {
            if(sllOperadorOperandos.length() != 2) {
                printf("Error diferente de dos operandos.\n");
                return;
            }
            else {
                slDestino = sllOperadorOperandos.first();
                slOrigen = sllOperadorOperandos.last();
                Verificar2Operandos(slDestino, slOrigen);
            }
        }
    }
    else if(slInstruccion.contains(QRegExp("mul"))) {
        emInstruccion = MUL;
        printf("MUL\n");
        slInstruccionAEjecutar = slInstruccion.replace("mul", "");
        printf("slInstruccionAEjecutar\n");
        QStringList sllOperadorOperandos  = slInstruccionAEjecutar.split(",");
        QString slDestino, slOrigen;
        if(!sllOperadorOperandos.isEmpty()) {
            if(sllOperadorOperandos.length() != 2) {
                printf("Error diferente de dos operandos.\n");
                return;
            }
            else {
                slDestino = sllOperadorOperandos.first();
                slOrigen = sllOperadorOperandos.last();
                Verificar2Operandos(slDestino, slOrigen);
            }
        }
    }
    else if(slInstruccion.contains(QRegExp("inc"))) {
        QString slDestino;
        emInstruccion = INC;
        printf("INC\n");
        slDestino = slInstruccion.replace("inc", "");

                Verificar1Operandos(slDestino);

    }
    else if(slInstruccion.contains(QRegExp("dec"))) {
        QString slDestino;
        emInstruccion = DEC;
        printf("DEC\n");
        slDestino = slInstruccion.replace("dec", "");
                Verificar1Operandos(slDestino);

    }
    //
    EvaluarInstruccion();
    for(int i=0; i < 8; i++)
    printf("reg[%d] = %d\n", i, registros[i]);
}

void CompilarPrograma(){

}

void EvaluarInstruccion() {
    switch(emInstruccion) {
    case MOV:
        switch(emTipoOperando) {
        case TO_REGISTRO_REGISTRO:
            registros[imValDestino] = registros[imValOrigen];
            programLength += 2;
            break;
        case TO_REGISTRO_INMEDIATO:
            registros[imValDestino] = imValOrigen ;
            break;
        case TO_INMEDIATO_REGISTRO:
            // Error
            break;
        case TO_REGISTRO_MEMORIA:
            registros[imValDestino] = memoria[imValOrigen].contenido;
            programLength += 3;
            break;
        case TO_MEMORIA_REGISTRO:
            memoria[imValDestino].contenido = registros[imValOrigen];
            break;
        default:
            break;
        }
        break;
    case ADD:
        switch(emTipoOperando) {
        case TO_REGISTRO_REGISTRO:
            registros[imValDestino] += registros[imValOrigen];
            break;
        case TO_REGISTRO_INMEDIATO:
            registros[imValDestino] += imValOrigen ;
            break;
        case TO_INMEDIATO_REGISTRO:
            // Error
            break;
        case TO_REGISTRO_MEMORIA:
            registros[imValDestino] += memoria[imValOrigen].contenido;
            break;
        case TO_MEMORIA_REGISTRO:
            memoria[imValDestino].contenido += registros[imValOrigen];
            break;
          default:
            break;
        }
        break;
    case SUB:
        switch(emTipoOperando) {
        case TO_REGISTRO_REGISTRO:
            registros[imValDestino] -= registros[imValOrigen];
            break;
        case TO_REGISTRO_INMEDIATO:
            registros[imValDestino] -= imValOrigen ;
            break;
        case TO_INMEDIATO_REGISTRO:
            // Error
            break;
        case TO_REGISTRO_MEMORIA:
            registros[imValDestino] -= memoria[imValOrigen].contenido;
            break;
        case TO_MEMORIA_REGISTRO:
            memoria[imValDestino].contenido -= registros[imValOrigen];
            break;
        default:
            break;
        }
        break;
    case MUL:
        switch(emTipoOperando) {
        case TO_REGISTRO_REGISTRO:
            registros[imValDestino] *= registros[imValOrigen];
            break;
        case TO_REGISTRO_INMEDIATO:
            registros[imValDestino] *= imValOrigen ;
            break;
        case TO_INMEDIATO_REGISTRO:
            // Error
            break;
        case TO_REGISTRO_MEMORIA:
            registros[imValDestino] *= memoria[imValOrigen].contenido;
            break;
        case TO_MEMORIA_REGISTRO:
            memoria[imValDestino].contenido *= registros[imValOrigen];
            break;
        default:
            break;
        }
        break;
    case DIV:
        switch(emTipoOperando) {
        case TO_REGISTRO_REGISTRO:
            registros[imValDestino] /= registros[imValOrigen];
            break;
        case TO_REGISTRO_INMEDIATO:
            registros[imValDestino] /= imValOrigen ;
            break;
        case TO_INMEDIATO_REGISTRO:
            // Error
            break;
        case TO_REGISTRO_MEMORIA:
            registros[imValDestino] /= memoria[imValOrigen].contenido;
            break;
        case TO_MEMORIA_REGISTRO:
            memoria[imValDestino].contenido /= registros[imValOrigen];
            break;
        default:
            break;
        }
        break;
    case INC:
        switch(emTipoOperando) {
        case TO_REGISTRO:
            registros[imValDestino]++;
            break;
        case TO_MEMORIA:
            memoria[imValDestino].contenido++;
            break;
        default:
            break;
        }
        break;
    case DEC:
        switch(emTipoOperando) {
        case TO_REGISTRO:
            registros[imValDestino]--;
            break;
        case TO_MEMORIA:
            memoria[imValDestino].contenido--;
            break;
        default:
            break;
        }
        break;
    case CMP:
        switch(emTipoOperando) {
        case TO_REGISTRO_REGISTRO:
            if(registros[imValDestino] == registros[imValOrigen])
                zf = false;
            else
                zf = true;
            break;
        case TO_REGISTRO_INMEDIATO:
            if(registros[imValDestino] == imValOrigen)
                zf = false;
            else
                zf = true;
            break;
        case TO_INMEDIATO_INMEDIATO:
            // Error el primer operando no puede ser un inmediato
            break;
        case TO_INMEDIATO_REGISTRO:
            if(imValDestino == registros[imValOrigen])
                zf = false;
            else
                zf = true;
            break;
        case TO_REGISTRO_MEMORIA:
            if(registros[imValDestino] == memoria[imValOrigen].contenido)
                zf = false;
            else
                zf = true;
            break;
        case TO_MEMORIA_REGISTRO:
            if(memoria[imValDestino].contenido == registros[imValOrigen])
                zf = false;
            else
                zf = true;
            break;
           default:
            break;
        }
        break;
    default:
        break;
    }
}
void Verificar1Operandos(QString spDestino) {
    int indd;
    if(spDestino.contains(QRegExp("reg"))) {
        printf("reg\n");
        bool ok;
        indd = spDestino.replace("reg", "").toInt(&ok);
        printf("%d\n", indd);
        if(!ok) {
            printf("error en el primer operando.");
        }
        else {
                emTipoOperando = TO_REGISTRO;
        }
    }
    else if(!spDestino.contains(QRegExp("["))) {
            printf("mem\n");
            QStringList sllDestino =  spDestino.split("[");
            QString slDestino = sllDestino.at(1);
            bool ok;
            indd = slDestino.split("]").first().toInt(&ok);
            printf("%d\n", indd);
            if(!ok) {
                printf("error en operando.");
            }
            else {
                emTipoOperando = TO_MEMORIA;
            }
    }
    imValDestino = indd;
}

void Verificar2Operandos(QString spDestino, QString spOrigen) {
    int indo = 0, indd = 0;
    if(spDestino.contains(QRegExp("reg")) && spOrigen.contains(QRegExp("reg"))) {
        printf("reg reg\n");
        bool ok;
        indd = spDestino.replace("reg", "").toInt(&ok);
        printf("%d\n", indd);
        if(!ok) {
            printf("error en el primer operando.");
        }
        else {
            indo = spOrigen.replace("reg", "").toInt(&ok);
            if(!ok) {
                printf("error en el segundo operando.");
            }
            else {
                emTipoOperando = TO_REGISTRO_REGISTRO;
            }
        }
    }
    else if(spDestino.contains(QRegExp("reg")) && !spOrigen.contains(QRegExp("reg"))) {
        printf("reg !reg\n");
        bool ok;
        indd = spDestino.replace("reg", "").toInt(&ok);
        if(!ok) {
            printf("error en el primer operando.");
        }
        else {
            indo = spOrigen.toInt(&ok);
            if(!ok) {
                printf("error en el segundo operando.");
            }
            else {
                emTipoOperando = TO_REGISTRO_INMEDIATO;
            }
        }
    }
    else if(!spDestino.contains(QRegExp("reg")) && !spOrigen.contains(QRegExp("reg"))) {
        printf("reg !reg\n");
        bool ok;
        indd = spDestino.replace("reg", "").toInt(&ok);
        if(!ok) {
            printf("error en el primer operando.");
        }
        else {
            indo = spOrigen.toInt(&ok);
            if(!ok) {
                printf("error en el segundo operando.");
            }
            else {
                emTipoOperando = TO_INMEDIATO_INMEDIATO;

            }
        }
    }
    else if(!spDestino.contains(QRegExp("reg")) && spOrigen.contains(QRegExp("reg"))) {
        printf("reg !reg\n");
        bool ok;
        indd = spDestino.replace("reg", "").toInt(&ok);
        if(!ok) {
            printf("error en el primer operando.");
        }
        else {
            indo = spOrigen.toInt(&ok);
            if(!ok) {
                printf("error en el segundo operando.");
            }
            else {
                emTipoOperando = TO_REGISTRO_INMEDIATO;

            }
        }
    }
    imValOrigen = indo;
    imValDestino = indd;
}

void ObtenerModelo() {
}

