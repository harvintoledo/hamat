/* codigo.h */
/**************************************************************
  **            UNIVERSIDAD NACIONAL DE INGENIER�A           **
  **    Proyecto Personal                                    **
  **    Compilador HAMAT                                     **
  **        |                                                **
  **        |                                                **
  **        V                                                **
  **        .--> Analizador L�xico                           **
  **        .--> Analizador Sint�ctico                       **
  **        .--> Analizador Sem�ntico                        **
  **        .--> Generador de C�digo Ensamblador             **
  **    Para lenguaje NOHEMI                                 **
  **                                                         **
  **    Autor                                                **
  **      Harvin Manuel Toledo Polanco                       **
  **      harvintoledo@gmail.com                             **
  *************************************************************/
#ifndef _CODIGO_H_
#define _CODIGO_H_

/* pc = contador de programa */
#define pc 7

/* mp = el "el apuntador de memoria" apunta
    a la parte superiro de la memoria (para almacenamiento temporal)
*/
#define mp 6

/* gp =el "apuntador global" apunta
    a la parte inferior de la memoria para 
    almacenamiento de variable (global)
    */
#define gp 5

/* acumulador */
#define ac 0

/* segundo acumulador */
#define ac1 1

/* utilidades de emisi�n de c�digo */
/*
    El procedimiento emitRO emite una
    instrucci�n solo de registro
    op = el opcode
    r = registro objetivo
    s = 1.er registro fuente
    t = 2.do registro fuente
    c = un comentario que para ser impreso si TraceCode es true
*/
void emitRO( char *op, int r, int s, int t, char *c );

/*
    El procedimiento emitRM emite una instruccion 
    de registro-a-memoria
    op = codigo de operacion
    r = registro objetivo
    d = el desplazamiento
    s = el registro base
    c = un comentrio si TraceCode es TRUE
    */
void emitRM( char *op, int r, int d, int s, char *c );

/*
    La funci�n emitSkip salta las localidades de c�digo "howMany"
    para reajuste posterior. Tambi�n
    devuelve la posici�n del c�digo actual 
*/
int emitSkip( int howMany);

/* el procedimiento emitBackup respalda a
    loc = una localidad previamente saltada
    */
void emitBackup( int loc );

/* 
    El procedimiento emitRestore restablece
    la posicion de codigo actual a la posici�n mas alta
    no emitida previamente
    */
    
void emitRestore( void );

/*
    El procedimiento emitComment imprime lineas de comentario
    con el comentrio c en el archivo d codigo
    */
void emitComment( char *c );

/*
    El procedimiento emitRM_Abs convierte una referencia absoluta
    en una referencia relativa al pc cuando se emite una
    intrucci�n de registro-a-memoria
    op = el opcode (c�digo operacional)
    r = registro objetivo
    a = la localidad absoluta en memoria
    c = un comentario para imprimirse si TraceCode es TRUE
*/
void emitRM_Abs( char *op, int r, int a, char *c);

#endif
