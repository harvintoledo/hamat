/* tablasimbolo.h */
#ifndef _TABSIMB_H
#define _TABSIMB_H

/* 
    El procedimiento st_insert inserta numeros de linea y
    localidades de memoria en la tabla de s�mbolos
    loc = localidad de memoria que se inserta �nicamente
    la primera vez, de otro modo se ignora
    */
void st_insert(char *nombre, int lineanumero, int localidad);

/*
    La funci�n st_lookup devuelve la localidad de
    memoria de una variable o -1 si no se encuentra
*/
int st_lookup(char *nombre);

/*
    el procedimiento printSymbTab imprime un listado
    formateado del contenido de la tabla de s�mbolos
*/
void imprimirTablaDeSimbolos(FILE *pArchivoDestino);

#endif
