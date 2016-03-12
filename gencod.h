/* gencod.h */
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
#ifndef _GENCOD_H_
#define _GENCOD_H_
/*  El procedimiento generarCodigo genera codigo hacia un
    archivo de c�digo por recorrido del �rbol sint�ctico. El
    segundo par�metro es el nombre de archivo
    del archivo de c�digo, y se utiliza para imprimir el
    nombre del archivo como un comentario en el archivo de c�digo
*/
void generarCodigo(NodoArbol *arbolSintactico, char *archivocodigo);

#endif
