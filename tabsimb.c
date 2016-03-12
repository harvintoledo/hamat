/* tabsimb.c*/
/*
	Implementación de la tabla de símbolos para
	el compilador HAMAT
	De momento permite solamente una tabla de símbolos
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabsimb.h"
/* TAM, es el tamaño de la tabla de disperción */
#define TAM 211
/* SHIFT es la potencia de dos emplead como multiplicador
	en la función de disperción */
#define SHIFT 4
/* la función de dispersión */
static int hash( char *clave)
{
	int temporal = 0;
	int i = 0;
	
	while(clave[i] != '\0')
	{
		temporal = ((temporal << SHIFT) + clave[i]) % TAM;
		i++;
	}
	
	return temporal;
}
/* la lista de números de línea del
	código fuente en el que es referenciada una variable
*/
typedef struct LineListRec
{
	int lineanumero;
	struct LineListRec * next;
} *LineList;
/*  El retgistro den las listas de cubetas pra
	cada variable, incluyendo nomobre,
	localidad de memoria de línea en los que
	aparece en el código fuente
	*/
typedef struct BucketListRec
{
	char *nombre;
	LineList lineas;
	int memloc; /* Localidad de memoria para variable */
	struct BucketListRec *next;
	
} *BucketList;
/* la tabla de dispersión */
static BucketList hashTable[TAM];
/* El procedimiento st_insert inserta números de línea y
	localidades de memoria en la tabla de símbolos
	loc = localidad de memoria que se inserta solamente la
	primera vez, de otro modo se ignora
*/
void st_insert(char *nombre, int lineanumero, int localidad)
{
	int h=hash(nombre);
	
	BucketList l = hashTable[h];
	
	while( (l != NULL) && (strcmp(nombre, l->nombre) != 0))
	l = l->next;
	
	if(l == NULL) /* variable que todavía no está en la tabla */
	{
		l = (BucketList) malloc(sizeof(struct BucketListRec));
		l->nombre = nombre;
		l->lineas = (LineList) malloc(sizeof(struct LineListRec));
		l->lineas->lineanumero = lineanumero;
		l->memloc = localidad;
		l->lineas->next = NULL;
		l->next = hashTable[h];
		hashTable[h] = l;
		
	}
	else /* está en la tabla de modo que solamente se agrega en 
		el número de la línea */
	{
		LineList t = l->lineas;
		while (t->next != NULL)
		t = t->next;
		t->next = (LineList) malloc(sizeof(struct LineListRec));
		t->next->lineanumero = lineanumero;
		t->next->next=NULL;
	}
}  /* fin de la función st_insert */
/*  La función st_lookup devuelve la localidad de
	memoria de una variable o -1 sino se encuetra
*/
int st_lookup(char *nombre)
{
	int h = hash(nombre);
	BucketList l = hashTable[h];
	while((l != NULL) && (strcmp(nombre, l->nombre) != 0))
	l = l->next;
	
	if( l == NULL )
	return -1;
	else
	return l->memloc;
}
/*  El procedimiento printSymTab imprime un listado
	formateado del contenido de la tabla de símbolos
	para el archivo de listado
*/
void imprimirTablaDeSimbolos(FILE *pArchivoDestino)
{
	int i;
	
	fprintf( pArchivoDestino, "Nombre variable\tLocalidad\tNumero linea\n");
	fprintf( pArchivoDestino, "---------------\t---------\t------------\n");
	
	for(i=0; i < TAM; i++)
	{
		if(hashTable[i] != NULL)
		{
			BucketList l = hashTable[i];
			
			while( l != NULL)
			{
				LineList t = l->lineas;
				fprintf( pArchivoDestino, "%-14s ", l->nombre);
				fprintf( pArchivoDestino, "-8d   ", l->memloc);
				
				while( t != NULL )
				{
					fprintf( pArchivoDestino, "%4d ", t->lineanumero);
					t = t->next;
				}
				fprintf( pArchivoDestino, "\n");
				l = l->next;
				
			} /* fin de ciclo while */
			
		} /* fin de condicional if */
		
	} /* fin de ciclo for */
	
} /* fin de función printSymbTab */
