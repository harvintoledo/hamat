/* analex.h */
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
#ifndef _ANALEX_H_
#define _ANALEX_H_

#ifndef MAXIMALONGITUDDELEXEMA
#define MAXIMALONGITUDDELEXEMA                64
#endif

/* 
    el arreglo almacena el lexema de cada token */
extern char cadenaDeLexema[MAXIMALONGITUDDELEXEMA+1];

/* 
    La funcion obtenerLexema regresa el lexema
    o token siguiente en el archivo */
NodoListaLexema *obtenerListaDeLexemas( void );
InformacionLexema obtenerLexemaInformacion( void );

#endif
