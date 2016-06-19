#include "clasemetaanasin.h"

ClaseMetaAnaSin::ClaseMetaAnaSin() {

}

/* funcion principal del analizador sintactico */
/* la funcion analizarSintaxis devuelve el arbol recien construido */
NodoArbol *ClaseMetaAnaSin::analizarSintaxis( NodoListaLexema *listaLex )
{
    NodoArbol *temporal;
    lista = listaLex;
    /* volvemos a abrir el archivo para hacer analisis sintactico */
    pArchivoOrigen=fopen(nombreArchivoCodigoFuente, "r");
    fprintf(pArchivoDestino, "\nRegistro del analisis sintactico y lexico para lenguaje nohemi */</span><br>\n");
    /* obtener el primer lexema para realizar analisis sintactico */
    fprintf(pArchivoAnaSin, "\nRegistro de recorrido sintactico recursivo");
    fprintf(pArchivoAnaSin, "\nRealizado por Harvin Manuel Toledo Polanco");
    fprintf(pArchivoAnaSin, "\nharvintoledo@gmail.com");

    temporal = programa();
    if( lista->informacionLexema.lexema != FINDEARCHIVO )
    errorSintactico("\nEl codigo no continua porque se ha encontrado final de archivo\n");
    return temporal;
}
/* fin de la funcion analizarSintaxis */
/* nota: no olvidar colocar los datos al árbol que servirá para
    el analizador semántico y el generador de código */
