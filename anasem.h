/* anasem.h */
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
  
#ifndef _ANASEM_H_
#define _ANASEM_H_

void construyeTablaSimbolo(NodoArbol *);

void typeCheck(NodoArbol *);

#endif



