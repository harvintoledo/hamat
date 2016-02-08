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
#define ARQUITECTURA_8BITS 8
#define ARQUITECTURA_16BITS 16
#define ARQUITECTURA_32BITS 32
#define TAM_PILA 65535
stMemoria *memoria, *pila;
int modelo;
int tam_modelo = 65536; // Se establece por defecto tama;o de programa small
int registros[8];
int programLength = 0;
int pc = 0; // Contador de programas
int sp = -1; // Puntero de pila o stack pointer
int ds = 0;
bool zf = false; // Flag de estado de cero, modificado despues de comparar dos numeros con CMP
bool cf = false; // Flag de suma o resta, modificado despues de hacer una operacion de suma o resta
bool bmModelo = false;
bool bmDataSegment = false;
bool bmCodeSegment = false;
void ReservarMemoria();
void CargarMemoriaConIndiceYSinContenido();
void Push(int);
int Pop();
void ObtenerModelo();
void EjecutarInstruccion(char *);
void Verificar1Operandos(QString);
void Verificar2Operandos(QString, QString);
void CompilarPrograma();
void EvaluarInstruccion();
void EnsamblarPrograma();
enum eInsrucciones {
    //#instruccion MOV
    //#COMENTARIO: La instrucción MOV es la instrucción más utilizada en un microprocesador.
    // Los datos son transferidos desde un registro u operando llamado fuente a hacia un registro llamado destino.
    // No se puede transferir entre dos registros directamente, ni entre dos valores de memoria. Antes de transferir
    // de una zona a otra es importante usar un destino como pivote y transferir desde ese destino hacia otra localidad.
    // Por ejemplo:
    // MOV DX, DATO1
    // MOV DATO2, DX
    MOV,
    ADD,
    SUB,
    MUL,
    DIV,
    //#instruccion AND
    //#COMENTARIO:
    // Si ambos bits comparados son 1, establece el resultado en 1.
    // Las demás condiciones dan como resultado 0.
    AND,
    //#instruccion OR
    //#COMENTARIO:
    // Si cualquiera (o ambos) de los bits comparados es 1, el resultado es 1.
    // Si ambos bits están en 0, el resultado es 0.
    OR,
    //#instruccion XOR
    //#COMENTARIO:
    // Si uno de los bits comparados es 0 y el otro 1, el resultado es 1.
    // Si ambos bits comparados son iguales (ambos 0 o ambos 1), el resultado es 0.
    XOR,
    //#instruccion XNOR
    //#COMENTARIO:
    // Si uno de los bits comparados es 0 y el otro 1, el resultado es 0.
    // Si ambos bits comparados son iguales (ambos 0 o ambos 1), el resultado es 1.
    XNOR,
    //#instruccion INC
    //#COMENTARIO:
    // Incrementa el contenido del registro en 1 o  el contenido de la memoria a la que hace referencia en 1
    // Formato: INC registro
    // INC [referencia a memoria]
    INC,
    //#instruccion DEC
    //#COMENTARIO:
    // Disminuye el contenido del registro en 1 o  el contenido de la memoria a la que hace referencia en 1
    // Formato: DEC registro
    // DEC [referencia a memoria]
    DEC,
    //#instruccion INT
    //#COMENTARIO:
    // Realiza interrupciones en el microprocesador para atender o realizar otras tares del sistema operativo
    // esta es una de las únicas instrucciones que interactuan directamente con el Sistema Operativo y lenguaje
    // A bajo nivel
    INT,
    //#instruccion PUSH
    //#COMENTARIO:
    // Inserta el valor del registro al que hace referencia o contenido de la memoria a la que apunta en la
    // cima de una pila preparada en  la memoria.
    // Formato: PUSH registro
    // PUSH [referencia a memoria]
    PUSH,
    //#instruccion POP
    //#COMENTARIO:
    // Obtiene el valor de la cima de la pila y lo inserta en un registro al que hace referencia
    // o en la memoria a la que apunta la instruccion
    // Formato: POP registro
    // POP [referencia a memoria]
    POP,
    //#instruccion JMP
    //#COMENTARIO:
    // Realiza un salto incondicional en un programa a cualquier lugar de la memoria de programa apuntado por una etiqueta
    // Previamente preparada
    // Formato: JMP etiqueta
    JMP,
    //#instruccion JMPZ
    //#COMENTARIO:
    // Realiza un salto condicional si el flag de estado es cero ZF = 0 en un programa a cualquier lugar de la memoria
    // de programa apuntado por una etiqueta. Esta instruccion normalmente se usa en conjunto con CMP.
    // Previamente preparada,
    // Formato: JMPZ etiqueta
    JMPZ,
    //#instruccion JMPNZ
    //#COMENTARIO:
    // Realiza un salto condicional si el flag de estado no es cero ZF = 1 en un programa a cualquier lugar de la memoria
    // de programa apuntado por una etiqueta. Esta instruccion normalmente se usa en conjunto con CMP.
    // Previamente preparada,
    // Formato: JMPNZ etiqueta
    JMPNZ,
    //#instruccion CMP
    //#COMENTARIO:
    // La instruccion CMP se utilizada para comparar dos valores Origen y destino.
    // El resultado de los dos numeros afectan las banderas: AF, CF, OF, PF, SF,ZF
    CMP,
    //#instruccion TEST
    //#COMENTARIO:
    TEST,
    //#instruccion NOT
    //#COMENTARIO:
    // La instrucción NOT solo invierte los bits en un byte o palabra en un registro o en memoria;
    // esto es, convierte los ceros en unos y los unos en ceros.
    NOT,
    LEA,
    LDS,
    LES,
    SHL,
    SHR
};
enum eTipoOperando {
    TO_REGISTRO_REGISTRO,
    TO_REGISTRO_INMEDIATO,
    TO_INMEDIATO_REGISTRO,
    TO_REGISTRO_MEMORIA,
    TO_MEMORIA_INMEDIATO,
    TO_MEMORIA_REGISTRO,
    TO_INMEDIATO_INMEDIATO,
    TO_REGISTRO,
    TO_MEMORIA,
    TO_INMEDIATO
};
enum eTipoOperacion {
    OPERACION_SUMA,
    OPERACION_RESTA,
    OPERACION_DIVISION,    OPERACION_MULIPLICACION
};
enum eCantidadOperandos {
    CO_UN_OPERANDO,
    CO_DOS_OPERANDO,
    CO_NINGUN_OPERANDO
};
enum eTipoError {
    TE_TODO_BIEN,
    TE_OPERANDO_DESTINO_NO_INMEDIATO,
    TE_OPERANDO_DESTINO_NO_REGISTRO,
    TE_OPERANDO_DESTINO_NO_MEMORIA,
    TE_OPERANDO_ORIGEN_NO_INMEDIATO,
    TE_OPERANDO_ORIGEN_NO_REGISTRO,
    TE_OPERANDO_ORIGEN_NO_MEMORIA
};
FILE *pArchivoEntrada, *pArchivoSalida;
eTipoOperando emTipoOperando;
eTipoOperacion emTipoOperacion;
eInsrucciones emInstruccion;
eTipoError emTipoError;
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
        printf("%s\n", caracteres);
        EjecutarInstruccion(caracteres);
        system("PAUSE");
        imNumeroLinea ++;
    }
    system("PAUSE");
    fclose ( pArchivoEntrada );
    printf("Probando compilador qt para Windows.\n");
    getchar();
    return a.exec();
}
void ReservarMemoria() {
    memoria = new stMemoria[tam_modelo];
    pila = new stMemoria[TAM_PILA];
}
void CargarMemoriaConIndiceYSinContenido() {
    for(int i = 0; i < tam_modelo; i++) {
        memoria[i].contenido = 0;
        memoria[i].indice = i;
        pila[i].contenido = 0;
        pila[i].indice = i;
    }
}
void Push(int ipContenido) {
    if((sp+1) > TAM_PILA )
    printf("Error overflow: pila desbordada");
    else {
        sp++;
        pila[sp].contenido = ipContenido;
    }
}
int Pop() {
    int ilContenido = 0;
    if((sp-1) < 0 )
    printf("Error underflow: no hay contenido en la pila");
    else {
        ilContenido = pila[sp].contenido;
        sp--;
    }
    return ilContenido;
}
void EnsamblarPrograma() {
    // Definir modelo
    // Establecer  variables o segmento de variables o datos
    // Establecer segmento de codigo o programa
    // Establecer segmento de pila
}
void CargarInstruccionEnMemoria(char *instruccion) {
    QString slInstruccion = QString("%1").arg(instruccion);
    QString slInstruccionAEjecutar;
    // Pasar cualquier instruccion a mayuscula
    slInstruccion = slInstruccion.toLower();
    // Retirar blancos de instruccion (espacios,tabuladores, etc.)
    slInstruccion = slInstruccion.simplified();
    if(slInstruccion.contains(QRegExp(";"))) {
        // Ignorar instruccion
        return;
    }
    else if(slInstruccion.contains(QRegExp("mov"))) {
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
}
void EjecutarInstruccion(char *instruccion) {
    QString slInstruccion = QString("%1").arg(instruccion);
    QString slInstruccionAEjecutar;
    // Pasar cualquier instruccion a mayuscula
    slInstruccion = slInstruccion.toLower();
    // Retirar blancos de instruccion (espacios,tabuladores, etc.)
    slInstruccion = slInstruccion.simplified();
    if(slInstruccion.contains(QRegExp(";"))) {
        // Ignorar instruccion
        return;
    }
    else if(slInstruccion.contains(QRegExp("mov"))) {
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
    else if(slInstruccion.contains(QRegExp("and"))) {
        emInstruccion = AND;
        printf("AND\n");
        slInstruccionAEjecutar = slInstruccion.replace("and", "");
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
    else if(slInstruccion.contains(QRegExp("or"))) {
        emInstruccion = OR;
        printf("OR\n");
        slInstruccionAEjecutar = slInstruccion.replace("or", "");
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
    else if(slInstruccion.contains(QRegExp("xor"))) {
        emInstruccion = XOR;
        printf("XOR\n");
        slInstruccionAEjecutar = slInstruccion.replace("xor", "");
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
    else if(slInstruccion.contains(QRegExp("xnor"))) {
        emInstruccion = MUL;
        printf("XNOR\n");
        slInstruccionAEjecutar = slInstruccion.replace("xnor", "");
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
    else if(slInstruccion.contains(QRegExp("push"))) {
        QString slDestino;
        emInstruccion = PUSH;
        printf("PUSH\n");
        slDestino = slInstruccion.replace("push", "");
        Verificar1Operandos(slDestino);
    }
    else if(slInstruccion.contains(QRegExp("pop"))) {
        QString slDestino;
        emInstruccion = POP;
        printf("POP\n");
        slDestino = slInstruccion.replace("pop", "");
        Verificar1Operandos(slDestino);
    }
    else if(slInstruccion.contains(QRegExp("test"))) {
        QString slDestino;
        emInstruccion = TEST;
        printf("TEST\n");
        slDestino = slInstruccion.replace("test", "");
        Verificar1Operandos(slDestino);
    }
    else if(slInstruccion.contains(QRegExp("not"))) {
        QString slDestino;
        emInstruccion = NOT;
        printf("NOT\n");
        slDestino = slInstruccion.replace("not", "");
        Verificar1Operandos(slDestino);
    }
    else if(slInstruccion.contains(QRegExp("lea"))) {
        QString slDestino;
        emInstruccion = LEA;
        printf("LEA\n");
        slDestino = slInstruccion.replace("lea", "");
        Verificar1Operandos(slDestino);
    }
    else if(slInstruccion.contains(QRegExp("lds"))) {
        QString slDestino;
        emInstruccion = LDS;
        printf("LDS\n");
        slDestino = slInstruccion.replace("lds", "");
        Verificar1Operandos(slDestino);
    }
    else if(slInstruccion.contains(QRegExp("les"))) {
        QString slDestino;
        emInstruccion = LES;
        printf("LES\n");
        slDestino = slInstruccion.replace("les", "");
        Verificar1Operandos(slDestino);
    }
    else if(slInstruccion.contains(QRegExp("shl"))) {
        emInstruccion = SHL;
        printf("SHL\n");
        slInstruccionAEjecutar = slInstruccion.replace("shl", "");
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
    else if(slInstruccion.contains(QRegExp("shr"))) {
        emInstruccion = SHR;
        printf("SHR\n");
        slInstruccionAEjecutar = slInstruccion.replace("shr", "");
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
    //
    EvaluarInstruccion();
    for(int i=0; i < 8; i++)
    printf("reg[%d] = %d\n", i, registros[i]);
    printf("memoria source: address:%d content:%d\n", imValOrigen, memoria[imValOrigen].contenido);
    printf("memoria dest: address:%d content:%d\n", imValDestino, memoria[imValDestino].contenido);
    printf("Cima pila[%d] = %d\n", sp, pila[sp].contenido);
}
void CompilarPrograma(){
}
void EvaluarInstruccion() {
    emTipoError = TE_TODO_BIEN;
    switch(emInstruccion) {
        //#principo instruccion MOV
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
            emTipoError = TE_OPERANDO_DESTINO_NO_INMEDIATO;
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
        //#fin instruccion MOV
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
            emTipoError = TE_OPERANDO_DESTINO_NO_INMEDIATO;
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
            emTipoError = TE_OPERANDO_DESTINO_NO_INMEDIATO;
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
            emTipoError = TE_OPERANDO_DESTINO_NO_INMEDIATO;
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
            emTipoError = TE_OPERANDO_DESTINO_NO_INMEDIATO;
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
    case AND:
        switch(emTipoOperando) {
        case TO_REGISTRO_REGISTRO:
            registros[imValDestino] &= registros[imValOrigen];
            break;
        case TO_REGISTRO_INMEDIATO:
            registros[imValDestino] &= imValOrigen ;
            break;
        case TO_INMEDIATO_REGISTRO:
            // Error
            emTipoError = TE_OPERANDO_DESTINO_NO_INMEDIATO;
            break;
        case TO_REGISTRO_MEMORIA:
            registros[imValDestino] &= memoria[imValOrigen].contenido;
            break;
        case TO_MEMORIA_REGISTRO:
            memoria[imValDestino].contenido &= registros[imValOrigen];
            break;
        default:
            break;
        }
        break;
    case OR:
        switch(emTipoOperando) {
        case TO_REGISTRO_REGISTRO:
            registros[imValDestino] |= registros[imValOrigen];
            break;
        case TO_REGISTRO_INMEDIATO:
            registros[imValDestino] |= imValOrigen ;
            break;
        case TO_INMEDIATO_REGISTRO:
            // Error
            emTipoError = TE_OPERANDO_DESTINO_NO_INMEDIATO;
            break;
        case TO_REGISTRO_MEMORIA:
            registros[imValDestino] |= memoria[imValOrigen].contenido;
            break;
        case TO_MEMORIA_REGISTRO:
            memoria[imValDestino].contenido |= registros[imValOrigen];
            break;
        default:
            break;
        }
        break;
    case XOR:
        switch(emTipoOperando) {
        case TO_REGISTRO_REGISTRO:
            registros[imValDestino] |= registros[imValOrigen];
            break;
        case TO_REGISTRO_INMEDIATO:
            registros[imValDestino] |= imValOrigen ;
            break;
        case TO_INMEDIATO_REGISTRO:
            // Error
            emTipoError = TE_OPERANDO_DESTINO_NO_INMEDIATO;
            break;
        case TO_REGISTRO_MEMORIA:
            registros[imValDestino] |= memoria[imValOrigen].contenido;
            break;
        case TO_MEMORIA_REGISTRO:
            memoria[imValDestino].contenido |= registros[imValOrigen];
            break;
        default:
            break;
        }
        break;
    case XNOR:
        switch(emTipoOperando) {
        case TO_REGISTRO_REGISTRO:
            registros[imValDestino] |= registros[imValOrigen];
            break;
        case TO_REGISTRO_INMEDIATO:
            registros[imValDestino] |= imValOrigen ;
            break;
        case TO_INMEDIATO_REGISTRO:
            // Error
            emTipoError = TE_OPERANDO_DESTINO_NO_INMEDIATO;
            break;
        case TO_REGISTRO_MEMORIA:
            registros[imValDestino] |= memoria[imValOrigen].contenido;
            break;
        case TO_MEMORIA_REGISTRO:
            memoria[imValDestino].contenido |= registros[imValOrigen];
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
    case PUSH:
        switch(emTipoOperando) {
        case TO_REGISTRO:
            Push(registros[imValDestino]);
            break;
        case TO_MEMORIA:
            Push(memoria[imValDestino].contenido);
            break;
        default:
            break;
        }
        break;
    case POP:
        switch(emTipoOperando) {
        case TO_REGISTRO:
            registros[imValDestino] = Pop();
            break;
        case TO_MEMORIA:
            memoria[imValDestino].contenido = Pop();
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
    case TEST:
        switch(emTipoOperando) {
        case TO_REGISTRO_REGISTRO:
            registros[imValDestino] &= registros[imValOrigen];
            break;
        case TO_REGISTRO_INMEDIATO:
            registros[imValDestino] &= imValOrigen ;
            break;
        case TO_INMEDIATO_REGISTRO:
            // Error
            emTipoError = TE_OPERANDO_DESTINO_NO_INMEDIATO;
            break;
        case TO_REGISTRO_MEMORIA:
            registros[imValDestino] &= memoria[imValOrigen].contenido;
            break;
        case TO_MEMORIA_REGISTRO:
            memoria[imValDestino].contenido &= registros[imValOrigen];
            break;
        default:
            break;
        }
        break;
    case NOT:
        switch(emTipoOperando) {
        case TO_REGISTRO:
            registros[imValDestino] = !registros[imValDestino];
            break;
        case TO_MEMORIA:
            memoria[imValDestino].contenido = !memoria[imValDestino].contenido;
            break;
        default:
            break;
        }
        break;
    case LEA:
        break;
    case LDS:
        break;
    case LES:
        break;
    case SHL:
        switch(emTipoOperando) {
        case TO_REGISTRO_REGISTRO:
            registros[imValDestino] <<= imValOrigen;
            break;
        case TO_REGISTRO_INMEDIATO:
            registros[imValDestino] <<= imValOrigen;
            break;
        case TO_INMEDIATO_REGISTRO:
            // Error
            emTipoError = TE_OPERANDO_DESTINO_NO_INMEDIATO;
            break;
        case TO_REGISTRO_MEMORIA:
            // Error
            registros[imValDestino] += memoria[imValOrigen].contenido;
            break;
        case TO_MEMORIA_REGISTRO:
            // Error
            memoria[imValDestino].contenido += registros[imValOrigen];
            break;
        case TO_MEMORIA_INMEDIATO:
            memoria[imValDestino].contenido <<= imValOrigen;
            break;
        default:
            break;
        }
        break;
    case SHR:
        switch(emTipoOperando) {
        case TO_REGISTRO_REGISTRO:
            registros[imValDestino] >>= imValOrigen;
            break;
        case TO_REGISTRO_INMEDIATO:
            registros[imValDestino] >>= imValOrigen;
            break;
        case TO_INMEDIATO_REGISTRO:
            // Error
            emTipoError = TE_OPERANDO_DESTINO_NO_INMEDIATO;
            break;
        case TO_REGISTRO_MEMORIA:
            // Error
            registros[imValDestino] += memoria[imValOrigen].contenido;
            break;
        case TO_MEMORIA_REGISTRO:
            // Error
            memoria[imValDestino].contenido += registros[imValOrigen];
            break;
        case TO_MEMORIA_INMEDIATO:
            memoria[imValDestino].contenido >>= imValOrigen;
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
        printf("!reg !reg\n");
        bool ok;
        if(spDestino.contains(QRegExp("["))) {
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
        else {
            indd = spDestino.toInt(&ok);
            if(!ok) {
                printf("error en operando.");
            }
            else {
                emTipoOperando = TO_INMEDIATO;
            }
        }
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
