#ifndef UTIL
#define UTIL
#ifndef MAXIMONUMERODEPALABRASRESERVADAS
#define MAXIMONUMERODEPALABRASRESERVADAS 100
#endif

/* numero maximo de hijos que tiene el arbol de analisis sintactico, aunque tiene
   hijos auxiliares como hijoauxiliar, o siguiente */
#ifndef MAXNUMHIJOS
#define MAXNUMHIJOS 4
#endif

#ifndef MAXIMALONGITUDDEALAMACENAMIENTO
#define MAXIMALONGITUDDEALAMACENAMIENTO       256
#endif

#ifndef MAXIMALONGITUDDELEXEMA
#define MAXIMALONGITUDDELEXEMA                64
#endif

#ifndef MAXCOL_COMMENT
#define MAXCOL_COMMENT                84
#endif

/* estados del automata del analizador lexico o reconocedor de lexemas */
typedef enum {
    INICIO, ENASIG, ENCOMPMAY, ENCOMPMEN, ENIGUALDAD, ENDIVISION, ENTRADACOMENT1,
    ENTRADACOMENT2, ENTRADACOMENTLIN, ENAND, ENOR,
    ENTRADANUMTIPOESTADO1, ENTRADANUMTIPOESTADO2, ENTRADANUMTIPOESTADO3,
    ENTRADANUMTIPOESTADO4, ENTRADANUMTIPOESTADO5, ENTRADANUMTIPOESTADO6, ENTRADANUMTIPOESTADO7,
    ENTRADANUMTIPOESTADO8, ENTRADANUMTIPOESTADO9, ENTRADANUMTIPOESTADO10, ENTRADANUMTIPOESTADO11,
    ENTRADANUMTIPOESTADO12, ENTRADANUMTIPOESTADO13, ENTRADANUMTIPOESTADO14, ENTRADANUMTIPOESTADO15,
    ENTRADANUMTIPOESTADO16, ENTRADANUMTIPOESTADO17,
    ENOPERACION, ENID, ENCADENA, HECHO
} TipoEstado;

/* Estados del analizador lexico */
typedef enum TipoLexema {
    /* lexema de administracion */
    COMIENZODEARCHIVO, FINDEARCHIVO, ERROR,
    /* palabras reservadas, en orden alfabetico para optimizacion de busqueda  */
    TIPO_LEXEMA_MOV, TIPO_LEXEMA_ADD,TIPO_LEXEMA_SUB, TIPO_LEXEMA_MUL,
    TIPO_LEXEMA_DIV, TIPO_LEXEMA_AND, TIPO_LEXEMA_OR, TIPO_LEXEMA_XOR,
    TIPO_LEXEMA_XNOR, TIPO_LEXEMA_INC, TIPO_LEXEMA_DEC, TIPO_LEXEMA_INT,
    TIPO_LEXEMA_PUSH, TIPO_LEXEMA_POP, TIPO_LEXEMA_JMP, TIPO_LEXEMA_JMPZ,
    TIPO_LEXEMA_JMPNZ, TIPO_LEXEMA_CMP, TIPO_LEXEMA_TEST, TIPO_LEXEMA_NOT,
    TIPO_LEXEMA_LEA, TIPO_LEXEMA_LDS, TIPO_LEXEMA_LES, TIPO_LEXEMA_SHL,
    TIPO_LEXEMA_SHR,
    /* lexemas de caracteres multiples */
    ID, IDNUM,  IDCADENA
} TipoLexema;
/* tabla de busquedas para las palabras reservadas */
static struct {
    char *cad;
    TipoLexema tok;
} palabraReservada[MAXIMONUMERODEPALABRASRESERVADAS] = {
    //#instruccion MOV
    //#COMENTARIO: La instrucción MOV es la instrucción más utilizada en un microprocesador.
    // Los datos son transferidos desde un registro u operando llamado fuente a hacia un registro llamado destino.
    // No se puede transferir entre dos registros directamente, ni entre dos valores de memoria. Antes de transferir
    // de una zona a otra es importante usar un destino como pivote y transferir desde ese destino hacia otra localidad.
    // Por ejemplo:
    // MOV DX, DATO1
    // MOV DATO2, DX
    { "mov", TIPO_LEXEMA_MOV},
    { "add", TIPO_LEXEMA_ADD},
    {"sub", TIPO_LEXEMA_SUB},
    { "mul", TIPO_LEXEMA_MUL},
    { "div", TIPO_LEXEMA_DIV},
    //#instruccion AND
    //#COMENTARIO:
    // Si ambos bits comparados son 1, establece el resultado en 1.
    // Las demás condiciones dan como resultado 0.
    { "and", TIPO_LEXEMA_AND},
    //#instruccion OR
    //#COMENTARIO:
    // Si cualquiera (o ambos) de los bits comparados es 1, el resultado es 1.
    // Si ambos bits están en 0, el resultado es 0.
    { "or", TIPO_LEXEMA_OR},
    //#instruccion XOR
    //#COMENTARIO:
    // Si uno de los bits comparados es 0 y el otro 1, el resultado es 1.
    // Si ambos bits comparados son iguales (ambos 0 o ambos 1), el resultado es 0.
    { "xor", TIPO_LEXEMA_XOR},
    //#instruccion XNOR
    //#COMENTARIO:
    // Si uno de los bits comparados es 0 y el otro 1, el resultado es 0.
    // Si ambos bits comparados son iguales (ambos 0 o ambos 1), el resultado es 1.
    { "xor", TIPO_LEXEMA_XNOR},
    //#instruccion INC
    //#COMENTARIO:
    // Incrementa el contenido del registro en 1 o  el contenido de la memoria a la que hace referencia en 1
    // Formato: INC registro
    // INC [referencia a memoria]
    { "inc", TIPO_LEXEMA_INC},
    //#instruccion DEC
    //#COMENTARIO:
    // Disminuye el contenido del registro en 1 o  el contenido de la memoria a la que hace referencia en 1
    // Formato: DEC registro
    // DEC [referencia a memoria]
    { "dec", TIPO_LEXEMA_DEC},
    //#instruccion INT
    //#COMENTARIO:
    // Realiza interrupciones en el microprocesador para atender o realizar otras tares del sistema operativo
    // esta es una de las únicas instrucciones que interactuan directamente con el Sistema Operativo y lenguaje
    // A bajo nivel
    { "int", TIPO_LEXEMA_INT},
    //#instruccion PUSH
    //#COMENTARIO:
    // Inserta el valor del registro al que hace referencia o contenido de la memoria a la que apunta en la
    // cima de una pila preparada en  la memoria.
    // Formato: PUSH registro
    // PUSH [referencia a memoria]
    { "push", TIPO_LEXEMA_PUSH},
    //#instruccion POP
    //#COMENTARIO:
    // Obtiene el valor de la cima de la pila y lo inserta en un registro al que hace referencia
    // o en la memoria a la que apunta la instruccion
    // Formato: POP registro
    // POP [referencia a memoria]
    { "pop", TIPO_LEXEMA_POP},
    //#instruccion JMP
    //#COMENTARIO:
    // Realiza un salto incondicional en un programa a cualquier lugar de la memoria de programa apuntado por una etiqueta
    // Previamente preparada
    // Formato: JMP etiqueta
    { "jmp", TIPO_LEXEMA_JMP},
    //#instruccion JMPZ
    //#COMENTARIO:
    // Realiza un salto condicional si el flag de estado es cero ZF = 0 en un programa a cualquier lugar de la memoria
    // de programa apuntado por una etiqueta. Esta instruccion normalmente se usa en conjunto con CMP.
    // Previamente preparada,
    // Formato: JMPZ etiqueta
    { "jmpz", TIPO_LEXEMA_JMPZ},
    //#instruccion JMPNZ
    //#COMENTARIO:
    // Realiza un salto condicional si el flag de estado no es cero ZF = 1 en un programa a cualquier lugar de la memoria
    // de programa apuntado por una etiqueta. Esta instruccion normalmente se usa en conjunto con CMP.
    // Previamente preparada,
    // Formato: JMPNZ etiqueta
    { "jmpnz", TIPO_LEXEMA_JMPNZ},
    //#instruccion CMP
    //#COMENTARIO:
    // La instruccion CMP se utilizada para comparar dos valores Origen y destino.
    // El resultado de los dos numeros afectan las banderas: AF, CF, OF, PF, SF,ZF
    { "cmp", TIPO_LEXEMA_CMP},
    //#instruccion TEST
    //#COMENTARIO:
    { "test", TIPO_LEXEMA_TEST},
    //#instruccion NOT
    //#COMENTARIO:
    // La instrucción NOT solo invierte los bits en un byte o palabra en un registro o en memoria;
    // esto es, convierte los ceros en unos y los unos en ceros.
    { "not", TIPO_LEXEMA_NOT},
    { "lea", TIPO_LEXEMA_LEA},
    { "lds", TIPO_LEXEMA_LDS},
    { "les", TIPO_LEXEMA_LES},
    { "shl", TIPO_LEXEMA_SHL},
    { "shr", TIPO_LEXEMA_SHR}
};

/* ExpType es utilizado para verificación de tipos */
typedef enum {
    Void,
    Entero,
    Booleano,
    Real,
    Caracter,
    Cadena
} ExpType;


typedef enum {
    TIPOARBOL_SENTENCIA_PARAMETRO,
    TIPOARBOL_SENTENCIA_TIPO_VARIABLE,
    TIPOARBOL_SENTENCIA_DECLARACION_LOCAL,
    TIPOARBOL_SENTENCIA_DECLARACION_GLOBAL,
    TIPOARBOL_FACTOR,
    TIPOARBOL_EXPRESION,
    TIPOARBOL_EXPRESION_SENTENCIA,
    TIPOARBOL_SENTENCIA_RETORNAR,
    TIPOARBOL_SENTENCIA_COMPUESTA,
    TIPOARBOL_SENTENCIA_PARAMETROS,
    TIPOARBOL_SENTENCIA_VAR,
    TIPOARBOL_DECLARACION_LOCAL,
    TIPOARBOL_SI_SENTENCIA,          TIPOARBOL_SENTENCIA_REPETIR, TIPOARBOL_SENTENCIA_MIENTRAS,
    TIPOARBOL_SENTENCIA_PARA,        TIPOARBOL_SENTENCIA_PROGRAMA,
    TIPOARBOL_SENTENCIA_DECLARACION, TIPOARBOL_SENTENCIA_FUNCION,  TIPOARBOL_SENTENCIA_PROCEDIMIENTO,
    TIPOARBOL_SENTENCIA_EXPLOG,      TIPOARBOL_SENTENCIA_CLASE,    TIPOARBOL_SENTENCIA_CARACTER,
    TIPOARBOL_SENTENCIA_ENTERO,      TIPOARBOL_SENTENCIA_REAL,     TIPOARBOL_SENTENCIA_CADENA,
    TIPOARBOL_SENTENCIA_SELECCIONAR, TIPOARBOL_LISTA_CASO_SENTENCIA, TIPOARBOL_CASO_SENTENCIA,
    TIPOARBOL_SENTENCIA_ALCONTRARIO
} TipoArbolSentencia;

typedef enum {
        TIPOARBOL_OPERADOR, TIPOARBOL_CONSTANTE, TIPOARBOL_IDENTIFICADOR,
        TIPOARBOL_CADENA, TIPOARBOL_LLAMADA, TIPOARBOL_VARIABLE,
        TIPOARBOL_ARGUMENTOS, TIPOARBOL_PARAMETROS_ACTUALES
} TipoArbolExpresion;

typedef enum {
    NodoDescendienteSentencia,
    NodoDescendienteExpresion
} NodoDescendiente;



typedef struct NodoArbol {
    /* indice 0 para el nodo del test */
    /* indice 1 puede servir para la rama sino del lenguaje */
    struct NodoArbol *hijo[MAXNUMHIJOS];
    struct NodoArbol *hijoextra; /* hijo extra para informacion */
    struct NodoArbol *siguiente; /* para crear un arbol que tenga varias variables o varias funciones */

    int lineanumero; /* cada nodo mantiene informacion de la linea correspondiente al codigo */

    NodoDescendiente nododescendiente;
    ExpType type; /* para la verficacion del tipo de expresiones */
    char nombre[256];

    union {
        TipoArbolSentencia tipoArbolSentencia;
        TipoArbolExpresion tipoArbolExpresion;
    } descendiente;

    union {
        TipoLexema tipoLexemaOperador;
        int val;
        char *nombre;
    } atributo;

    double valor;

} NodoArbol;

typedef struct InformacionLexema {
    TipoLexema lexema;
    char informacion[256]; /* cadena con contenido de valor, puede ser numero o una cadena a imprimir */
    int lineanumero; /* linea en donde aparece el lexema */
    int profundidad; /* profundidad del lexema */
    int orden; /* orden en el que aparece en una sentencia */
} InformacionLexema;

typedef struct NodoListaLexema {
    InformacionLexema informacionLexema;

    NodoListaLexema *anterior;
    NodoListaLexema *siguiente;

} NodoListaLexema;
#endif // UTIL
