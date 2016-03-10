/* gencod.h */
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
#ifndef _GENCOD_H_
#define _GENCOD_H_
/*  El procedimiento generarCodigo genera codigo hacia un
    archivo de código por recorrido del árbol sintáctico. El
    segundo parámetro es el nombre de archivo
    del archivo de código, y se utiliza para imprimir el
    nombre del archivo como un comentario en el archivo de código
*/
void generarCodigo(NodoArbol *arbolSintactico, char *archivocodigo);

#endif
