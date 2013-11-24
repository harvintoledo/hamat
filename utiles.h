/* utiles.h */
/* Archivo de cabecera para funciones utiles para el compilador HAMAT */
/**************************************************************
  **            UNIVERSIDAD NACIONAL DE INGENIERÍA           **
  **    Proyecto Personal                                    **
  **    Compilador HAMAT                                     **
  **        |                                                **
  **        |                                                **
  **        V                                                **
  **        .--> Analizador Léxico                           **
  **        .--> Analizador Sintáctico                       **
  **        .--> Analizador Semántico                        **
  **        .--> Generador de Código Ensamblador             **
  **    Para lenguaje NOHEMI                                 **
  **                                                         **
  **    Autor                                                **
  **      Harvin Manuel Toledo Polanco                       **
  **      harvintoledo@gmail.com                             **
  *************************************************************/
#ifndef _UTILES_H
#define _UTILES_H


void imprimirLexema(TipoLexema, const char *);
void imprimirLexemaParaLista(TipoLexema lex);

/* prototipo de funciones para llamadas recursivas */
/* la funcion nuevoNodoSentencia crea un nuevo nodo de sentencia para la construccion del arbol sintactico */
NodoListaLexema *nuevoNodoLexema( InformacionLexema lex );
NodoArbol *nuevoNodoSentencia( TipoArbolSentencia );
/* la funcion nuevoNodoExpresion crea un nuevo nodo de expresion para la construccion del arbol sintactico */
NodoArbol *nuevoNodoExpresion( TipoArbolExpresion );

/* La funcion copiar cadena crea una nueva copia de una cadena existente */
char *copiarCadena( char * );

/* Esta función imprime el arbol del analisis sintáctico para el lenguaje Nohemi
*/
void imprimirArbol( NodoArbol *);

#endif
