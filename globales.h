/**************************************************************
  **    Proyecto Personal                                    **
  **    Compilador HAMAT                                     **
  **        |                                                **
  **        |                                                **
  **        V                                                **
  **        .--> Analizador Léxico                           **
  **        .--> Analizador Sintáctico                       **
  **        .--> Analizador Semántico                        **
  **        .--> Generador de Código Ensamblador             **
  **    Para lenguaje ALEXANDRA                              **
  **                                                         **
  **    Autor                                                **
  **      Harvin Manuel Toledo Polanco                       **
  **      harvintoledo@gmail.com                             **
  *************************************************************/

#ifndef _GLOBALES_H
#define _GLOBALES_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef VERDADERO
#define VERDADERO                             1
#endif

#ifndef FALSO
#define FALSO                                 0
#endif

/* cantidad de palabras reservadas para el lenguaje nohemi */
#ifndef MAXIMONUMERODEPALABRASRESERVADAS
#define MAXIMONUMERODEPALABRASRESERVADAS      31
#endif

/* Estados del analizador lexico */
typedef enum TipoLexema
{
  /* lexema de administracion */
  COMIENZODEARCHIVO, FINDEARCHIVO, ERROR, 
  /* palabras reservadas, en orden alfabetico para optimizacion de busqueda  */
  VOID, ACCESO, ARREGLO, CADENA, CARACTER, CLASE, COMIENZO, DE, ENTERO,
  ENTONCES, FIN, FUNCION, HACER, HASTA, MIENTRAS, PARA,
  PROCEDIMIENTO, PROGRAMA, REAL, REPETIR, SI, SINO, VAR, LLAMAR,
  RETORNAR, SELECCIONAR, CASO, INTERRUMPIR, ALCONTRARIO,
  /* lexemas de caracteres multiples */
  ID, IDNUM,  IDCADENA,
  /* simbolos especiales */
  ASIGNACION, IGUALQUE, DIFERENTE, MAYORQUE, MENORQUE, MA_IQUE, MEN_IQUE,
  /* aritmeticos */
  MAS, MENOS, POR, ENTRE, PAREN_DER, PAREN_IZQ, LLAVE_DER, LLAVE_IZQ,
  PARENTESISCUADRADO_IZQ, PARENTESISCUADRADO_DER, OPERADOR_COMA,
  PUNTOYCOMA, PUNTOFINAL, DOSPUNTOS, DOBLECOMILLA, COMILLASIMPLE,
  /* logicos */
  OR, AND,
  
  /* acceso a secciones de una clase*/
  PRIVADO, PUBLICO, PROTEGIDO
} TipoLexema;

/* variables globales */
extern FILE *pArchivoOrigen;
extern FILE *pArchivoDestino;
extern FILE *pantalla;
extern FILE *codigo;
extern FILE *pArchivoAnaSin;
extern int  lineanumero;
extern char cadenaSalida[256];
extern char nombreArchivoCodigoFuente[256];
extern char nombreArchivoResultadoCompilacion[256];
extern char nombreArchivoCodigoIntermedio[256];
extern char nombreArchivoArbolDeSintaxis[256];
extern char nombreArchivoTokenDeComprobacion[256];

/* ExpType es utilizado para verificación de tipos */
typedef enum
/* { Void, Integer, Boolean } ExpType;*/
{Void, Entero, Booleano, Real, Caracter, Cadena} ExpType;


typedef enum 
{
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
    TIPOARBOL_SENTENCIA_SELECCIONAR, TIPOARBOL_CASO_SENTENCIA } TipoArbolSentencia;

typedef enum 
{
        TIPOARBOL_OPERADOR, TIPOARBOL_CONSTANTE, TIPOARBOL_IDENTIFICADOR,
        TIPOARBOL_CADENA, TIPOARBOL_LLAMADA, TIPOARBOL_VARIABLE,
        TIPOARBOL_ARGUMENTOS, TIPOARBOL_PARAMETROS_ACTUALES
} TipoArbolExpresion;

typedef enum
{ NodoDescendienteSentencia, NodoDescendienteExpresion } NodoDescendiente;

/* numero maximo de hijos que tiene el arbol de analisis sintactico, aunque tiene
   hijos auxiliares como hijoauxiliar, o siguiente */
#ifndef MAXNUMHIJOS
#define MAXNUMHIJOS 4
#endif

typedef struct NodoArbol
{
    /* indice 0 para el nodo del test */
    /* indice 1 puede servir para la rama sino del lenguaje */
    struct NodoArbol *hijo[MAXNUMHIJOS];
    struct NodoArbol *hijoextra; /* hijo extra para informacion */
    struct NodoArbol *siguiente; /* para crear un arbol que tenga varias variables o varias funciones */
  
    int lineanumero; /* cada nodo mantiene informacion de la linea correspondiente al codigo */

    NodoDescendiente nododescendiente;
    ExpType type; /* para la verficacion del tipo de expresiones */
    char nombre[256];
    
    union
    {
        TipoArbolSentencia tipoArbolSentencia; 
        TipoArbolExpresion tipoArbolExpresion; 
    } descendiente;

    union
    {
        TipoLexema tipoLexemaOperador; 
        int val;
        char *nombre;
    } atributo;
    
    double valor;
  
} NodoArbol;

typedef struct InformacionLexema
{
    TipoLexema lexema;
    char informacion[256]; /* cadena con contenido de valor, puede ser numero o una cadena a imprimir */
    int lineanumero; /* linea en donde aparece el lexema */
    int profundidad; /* profundidad del lexema */
    int orden; /* orden en el que aparece en una sentencia */
}InformacionLexema;

typedef struct NodoListaLexema
{
    InformacionLexema informacionLexema;
    
    NodoListaLexema *anterior;
    NodoListaLexema *siguiente;
    
}NodoListaLexema;


/* Marcas para seguimiento de código */
/*
    EchoSource = VERDADERO causa que le programa fuente se
    replique en el archivo de listado con números de línea
    durante el análisis sintáctico
*/
extern int EchoSource;

/*
    imprimeAnalisisLexico = VERDADERO ocasiona que la información de token sea
    impresa al archivo de listado a medida que cada token sea 
    reconocido, sirve para colorear la gramatica y exportarla a html
    */
extern int imprimeAnalisisLexico;

/* TraceParse = VERDADERO provoca que el árbol sintáctico sea
    impreso en el archivo de listado en forma linealizada
    (utilizando sangrías para los hijos)
*/

extern int imprimeAnalisisSintactico ;
/*  imprimeAnalisisSintactico  = VERDADERO provoca que la tabla de símbolos inserte
    y busque para informarlo al archivo listado 
*/
extern int TraceCode;
/* TraceCode = VERDADERO causa que se escriban comentarios
    al archivo de código TM a medida que se genera el código
    */
extern int TraceAnalize;

/* imprime el arbol sintactico para examinarlo cuando sea necesario */
extern int imprimeArbolSintactico;

/* genera pagina html de codigo de lenguaje nohemi */
extern int imprimeCodigoHtml;

/* Error = VERDADERO evita pasos adicionales si se presenta un error */
extern int Error;

#endif
