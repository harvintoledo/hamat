/* principal.c */
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
/* Este invoca a todo los procedimientos */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "globales.h"
#include "analex.h"
#include "anasin.h"
#include "gencod.h"
#include "utiles.h"

/* Marcas para seguimiento de código */
/*
    EchoSource = VERDADERO causa que le programa fuente se
    replique en el archivo de listado con números de línea
    durante el análisis sintáctico
*/
int EchoSource;

/*
    imprimeAnalisisLexico = VERDADERO ocasiona que la información de token sea
    impresa al archivo de listado a medida que cada token sea 
    reconocido, sirve para colorear la gramatica y exportarla a html
    */
int imprimeAnalisisLexico = VERDADERO;

/* TraceParse = VERDADERO provoca que el árbol sintáctico sea
    impreso en el archivo de listado en forma linealizada
    (utilizando sangrías para los hijos)
*/

int imprimirAnalisisSintactico = VERDADERO;
/*  imprimirAnalisisSintactico  = VERDADERO provoca que la tabla de símbolos inserte
    y busque para informarlo al archivo listado 
*/
int TraceCode = VERDADERO;
/* TraceCode = VERDADERO causa que se escriban comentarios
    al archivo de código TM a medida que se genera el código
    */
int TraceAnalize;

/* imprimir el arbol sintactico para examinarlo cuando sea necesario */
int imprimirArbolSintactico = VERDADERO ;

/* genera pagina html de codigo de lenguaje nohemi */
int imprimirCodigoHtml;

/* Error = VERDADERO evita pasos adicionales si se presenta un error */
int Error;

int generarCodigoIntermedio = VERDADERO;

/* variables globales */
FILE *pArchivoOrigen;
FILE *pArchivoDestino;
FILE *pantalla;
FILE *codigo;
FILE *pArchivoAnaSin;

NodoListaLexema *listaLexemas;

/* variables con nombre de archivos usados por los modulos:
    analizador léxico, analizador sintáctico, analizador semántico
    y generador de código intermedio */
char nombreArchivoCodigoFuente[256];
char nombreArchivoResultadoDeCompilacion[256];
char nombreArchivoCodigoIntermedio[256];
char nombreArchivoArbolDeSintaxis[256];
char nombreArchivoTokenDeComprobacion[256];
char nombreArchivoRegistroAnaSin[256];

int  lineanumero;

/* variables locales a principal.c */
/* variables para hacer la fecha en español */
char mes[12][11]={"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
char dia[7][11]={"Domingo","Lunes","Martes","Miercoles","Jueves","Viernes","Sabado"};

void Encabezado(void)
{
  fprintf(pArchivoDestino, "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n");
  fprintf(pArchivoDestino, "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n");
  fprintf(pArchivoDestino, "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n");
  fprintf(pArchivoDestino, "<head>\n");
  fprintf(pArchivoDestino, "<title>programa1.nohemi</title>\n");
  fprintf(pArchivoDestino, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\" />\n");
  fprintf(pArchivoDestino, "<meta name=\"generator\" content=\"Analizador y Coloreador de Gramaticas - COMPILADOR HAMAT\" />\n");
  fprintf(pArchivoDestino, "<meta name=\"author\" content=\"Harvin Manuel Toledo Polanco\" />\n");
  fprintf(pArchivoDestino, "<meta name=\"keywords\" content=\"harvin,toledo, compiladores, nohemi, analizador, parsing, sintatico, semantico\" />\n");
  fprintf(pArchivoDestino, "<style type=\"text/css\">\n");
  fprintf(pArchivoDestino, "<!--\n");
  fprintf(pArchivoDestino, "body {color: #000000; background-color: #FFFFFF; }\n");
  fprintf(pArchivoDestino, ".nohemi-ensamblador { color: #000000; }\n");
  fprintf(pArchivoDestino, ".nohemi-caracter { color: #000000; }\n");
  fprintf(pArchivoDestino, ".nohemi-comentario { color: #008000; }\n");
  fprintf(pArchivoDestino, ".nohemi-flotante { color: #000000; }\n");
  fprintf(pArchivoDestino, ".nohemi-hexadecimal { color: #000000; }\n");
  fprintf(pArchivoDestino, ".nohemi-identificador { color: #002200; font-weight: bold; }\n");
  fprintf(pArchivoDestino, ".nohemi-caracterilegal { color: #FF0000; }\n");
  fprintf(pArchivoDestino, ".nohemi-numero { color: #000000; }\n");
  fprintf(pArchivoDestino, ".nohemi-octal { color: #000000; }\n");
  fprintf(pArchivoDestino, ".nohemi-preprocesador { color: #0000FF; }\n");
  fprintf(pArchivoDestino, ".nohemi-palabrareservada { color: #0000FF; font-weight: bold;  }\n");
  fprintf(pArchivoDestino, ".nohemi-espacio { background-color: #FFFFFF; }\n");
  fprintf(pArchivoDestino, ".nohemi-cadena { color: #FF00FF; font-weight: bold; }\n");
  fprintf(pArchivoDestino, ".nohemi-simbolo { color: #000000; }\n");
  fprintf(pArchivoDestino, "-->\n");
  fprintf(pArchivoDestino, "</style>\n");
  fprintf(pArchivoDestino, "</head>\n");
  fprintf(pArchivoDestino, "<body>\n");
  fprintf(pArchivoDestino, "<pre>\n");
  fprintf(pArchivoDestino, "<code>\n");
  fprintf(pArchivoDestino, "<span style=\"font:12pt Courier New \"");
  
} /* fin de la funcion Encabezado */

void EncabezadoFecha( void )
{
	struct tm *fh;
    time_t tiempoActual;
	double segundos;
	
	time(&tiempoActual);
	fh=localtime(&tiempoActual);
	fprintf(pArchivoDestino, "<span class=\"nohemi-comentario\">/**  Fecha de Registro de Compilacion: </span><br>\n");
	fprintf(pArchivoDestino, "<span class=\"nohemi-comentario\">%s %d de %s de %d</span><br>\n",dia[fh->tm_wday],fh->tm_mday,mes[fh->tm_mon],fh->tm_year+1900);

	fh=localtime(&tiempoActual);
	fprintf(pArchivoDestino, "<span class=\"nohemi-comentario\">/**  Hora  de Registro de Compilacion: </span><br>");
	fprintf(pArchivoDestino, "<span class=\"nohemi-comentario\">%d:%d\'%d\"*/</span><br>\n",fh->tm_hour,fh->tm_min,fh->tm_sec);
	
} /* fin de la funcion EncabezadoFecha */

int main()
{
    NodoArbol *arbolSintactico;
    TipoLexema lex;
    NodoListaLexema *nodoLex;
  
    int i;
    
    /* nombre de archivo de codigo fuente */
    sprintf(nombreArchivoCodigoFuente, "");
    sprintf(nombreArchivoCodigoFuente, "%s", "trinomio.nohe");
    sprintf(nombreArchivoResultadoDeCompilacion, "%s", "resultado2.hta");
    sprintf(nombreArchivoRegistroAnaSin, "%s", "anasinordenacion6.txt");
    sprintf(nombreArchivoCodigoIntermedio, "%s", "archivo2.emsb");
    
    /*agregarATablaDeSimbolos(char *identif,  char caracter, 
     long entero, double real, char *cadena, double (*funcion)(double))*/
  
    pArchivoDestino=fopen(nombreArchivoResultadoDeCompilacion, "w");
    Encabezado();
    EncabezadoFecha();
  
    /* copiar primero archivo origen en archivo destino para tener una idea de como es el original */
    fprintf(pArchivoDestino, "\n<span class=\"nohemi-comentario\">/* Compilacion de lenguaje nohemi<br>\n");
    
    /* modulo analisis lexico */
    /* modulo que imprimir codigo fuente completo, a partir de analizador lexico */
    /*
    lineanumero=0;
    pArchivoOrigen=fopen(nombreArchivoCodigoFuente, "r");
    while(obtenerLexema() != FINDEARCHIVO);
    /* cerrar archivo y poner a cero los numeros de lineas para analizar */
    // fclose(pArchivoOrigen);
    /* fin modulo analisis lexico */

    nodoLex = obtenerListaDeLexemas();
    
    /* modulo analisis sintactico */
    
    pArchivoAnaSin = fopen(nombreArchivoRegistroAnaSin, "w");
    arbolSintactico = analizarSintaxis(nodoLex);
    fclose(pArchivoAnaSin);
    
    //if(arbolSintactico != NULL && imprimirArbolSintactico == VERDADERO)
        imprimirArbol(arbolSintactico);
        
    fclose(pArchivoOrigen);
    /* fin modulo analisis sintactico */
    
    fprintf(pArchivoDestino, "</code>\n");
    fprintf(pArchivoDestino, "</pre>\n");
    fprintf(pArchivoDestino, "</body>");
    fprintf(pArchivoDestino, "</xml>");
    fclose(pArchivoDestino);
    
    if(generarCodigoIntermedio)
    {
        char *archivocodigo;
        
        codigo = fopen(nombreArchivoCodigoIntermedio, "w");
        if(codigo == NULL)
            exit(1);
        generarCodigo(arbolSintactico, nombreArchivoCodigoIntermedio);
    }
  
} /* fin de la funcion main */
