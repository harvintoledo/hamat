/* analex.c */
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
**    Para lenguaje ALEXANDRA                              **
**                                                         **
**    Autor                                                **
**      Harvin Manuel Toledo Polanco                       **
**      harvintoledo@gmail.com                             **
*************************************************************/
#include "globales.h"
#include "utiles.h"
#include "analex.h"
#include <stdio.h>

/* estados del automata del analizador lexico o reconocedor de lexemas */
typedef enum
{
	INICIO, ENASIG, ENCOMPMAY, ENCOMPMEN, ENIGUALDAD, ENDIVISION, ENTRADACOMENT1, 
	ENTRADACOMENT2, ENTRADACOMENTLIN, ENAND, ENOR, 
	ENTRADANUMTIPOESTADO1, ENTRADANUMTIPOESTADO2, ENTRADANUMTIPOESTADO3,
	ENTRADANUMTIPOESTADO4, ENTRADANUMTIPOESTADO5, ENTRADANUMTIPOESTADO6, ENTRADANUMTIPOESTADO7,
	ENTRADANUMTIPOESTADO8, ENTRADANUMTIPOESTADO9, ENTRADANUMTIPOESTADO10, ENTRADANUMTIPOESTADO11,
	ENTRADANUMTIPOESTADO12, ENTRADANUMTIPOESTADO13, ENTRADANUMTIPOESTADO14, ENTRADANUMTIPOESTADO15,
	ENTRADANUMTIPOESTADO16, ENTRADANUMTIPOESTADO17,
	ENOPERACION, ENID, ENCADENA, HECHO,
	// Nuevos estados para reconocer entradas del meta-assembler
	ENNUMERAL,
} TipoEstado;

char cadenaDeLexema[MAXIMALONGITUDDELEXEMA+1];

/*
	longitud de buffer para las entradas
	estas sirven para las lineas del código fuente
*/
#ifndef MAXIMALONGITUDDEALAMACENAMIENTO
#define MAXIMALONGITUDDEALAMACENAMIENTO       256
#endif

static char almacenadorDeLinea[MAXIMALONGITUDDEALAMACENAMIENTO];
static int  lineaposicion = 0; /* posición actual en la linea que se lee */
static int  tamAlmacenamiento = 0; /* tamaño actual de la cadena del buffer */

static char obtenerSiguienteCaracter(void)
{
	if(!(lineaposicion < tamAlmacenamiento) )
	{
		lineanumero++;
		if( fgets(almacenadorDeLinea, MAXIMALONGITUDDEALAMACENAMIENTO-1, pArchivoOrigen) )
		{
			// fprintf(pArchivoDestino, "<br>%s",almacenadorDeLinea);
			tamAlmacenamiento = strlen( almacenadorDeLinea);
			lineaposicion=0;
			return almacenadorDeLinea[lineaposicion++];
		}
		else
		return EOF;
	}
	else
	return almacenadorDeLinea[lineaposicion++];
	
} /* fin de la funcion obtenerSiguienteCaracter */


void deshacerCaracter(void)
{
	lineaposicion--;
}

char bSiguienteCaracter(void)
{
	char c;
	lineaposicion++;
}

/* tabla de busquedas para las palabras reservadas */
static struct
{
	char *cad;
	TipoLexema tok;
} palabraReservada[MAXIMONUMERODEPALABRASRESERVADAS] = {
	{"funcion", FUNCION},
	{"acceso", ACCESO}, {"arreglo", ARREGLO}, 
	{"cadena", CADENA},{"caracter", CARACTER},{"clase", CLASE},{"comienzo", COMIENZO},{"de", DE}, {"entero", ENTERO}, 
	{"entonces", ENTONCES}, {"fin", FIN}, {"funcion", FUNCION}, 
	{"hacer", HACER}, {"hasta", HASTA}, {"mientras", MIENTRAS}, 
	{"para", PARA}, {"procedimiento", PROCEDIMIENTO}, {"programa", PROGRAMA},
	{"real", REAL}, {"repetir", REPETIR}, 
	{"si", SI}, {"sino", SINO}, {"var", VAR},
	
	{"retornar", RETORNAR}, {"privado", PRIVADO}, {"publico", PUBLICO}, {"protegido", PROTEGIDO},
	
	{"seleccionar", SELECCIONAR}, {"caso", CASO},
	
	{"interrumpir", INTERRUMPIR}, {"alcontrario", ALCONTRARIO}};

/*  busca un identificador y verifica que este sea una
	palabra reservada 
	*/ 
TipoLexema buscarPalabraReservada(char *s)
{
	int i;

	for(i=0; i < MAXIMONUMERODEPALABRASRESERVADAS; i++)
	if( !strcmp(s, palabraReservada[i].cad))
	return palabraReservada[i].tok;
	
	return ID;
} /* fin de la funcion buscarPalabraReservada */

/* función principal del analizador léxico
	este regresa el token a medida que va avanzando
	en el rastreo de codigo fuente
	*/

/* Construir lista de lexemas a partir de archivo */
NodoListaLexema *obtenerListaDeLexemas( void )
{
	NodoListaLexema *listaLexemas, *torax, *temporal;
	InformacionLexema lex;
	listaLexemas = NULL;
	
	lineanumero = 0;
	
	/* abrir archivo que contiene codigo fuente del lenguaje nohemi */
	pArchivoOrigen = fopen(nombreArchivoCodigoFuente, "r");
	
	lex.lexema = COMIENZODEARCHIVO;
	
	while( lex.lexema != FINDEARCHIVO)
	{ 
		lex = obtenerLexemaInformacion();
		/* si la lista esta todavia sin tokens */
		if(listaLexemas == NULL )
		{
			listaLexemas = nuevoNodoLexema(lex);
			listaLexemas->anterior = NULL;
			listaLexemas->siguiente = NULL;
		}
		/* construir un nuevo nodo y agregarlo a la lista de tokens */
		else
		{
			
			torax = nuevoNodoLexema(lex);
			torax->anterior = NULL;
			torax->siguiente = NULL;
			
			temporal = listaLexemas;
			/* buscar la cola de la lista de tokens */
			while( temporal->siguiente != NULL)
			temporal=temporal->siguiente;
			
			temporal->siguiente = torax;
			torax->anterior = temporal;
		}
		
	} /* fin de sentencia while*/
	
	/* anexar dos cadenas nulas para evitar conflictos de memoria en 
		el proceso de análisis sintáctico */
	temporal = listaLexemas;
	/* buscar la cola de la lista de tokens */
	while( temporal->siguiente != NULL)
	temporal=temporal->siguiente;
	
	temporal->siguiente = nuevoNodoLexema(lex);
	temporal->siguiente->siguiente = nuevoNodoLexema(lex);
	temporal->siguiente->siguiente->siguiente=NULL;
	
	fclose(pArchivoOrigen);
	
	return listaLexemas;
} /* fin de función obtenerListaDeLexemas */

InformacionLexema obtenerLexemaInformacion(void)
{
	/* indice para el almacenamiento del lexema de cadena */
	int indiceCadenaLexema = 0;

	/* mantiene el lexema actual que se devolverïo */
	InformacionLexema lexemaActual;
	/* estado actual del automata, siempre comienza en INICIO */
	TipoEstado estado = INICIO;

	/* marca para guardar la cadena en buffer */
	int bGuardarEnIdentificador;

	/* mientras el estado del autïomata no sea HECHO */
	while( estado != HECHO)
	{
		char c = obtenerSiguienteCaracter();
		bGuardarEnIdentificador = VERDADERO;
		
		switch(estado)
		{
		case INICIO:
			if( c == '0' )
			{
				estado = ENTRADANUMTIPOESTADO9;
				lexemaActual.lexema = IDNUM;
			}
			else
			if( isdigit(c) )
			{
				lexemaActual.lexema = IDNUM;
				estado = ENTRADANUMTIPOESTADO1;
			}
			else
			if( c == '.' )
			estado = ENTRADANUMTIPOESTADO4;
			else
			if( isalpha(c) || c == '_')
			estado = ENID;
			else
			/* ignorar espacios en blanco */
			if( c == ' ' || c == '\t' || c == '\n' )
			{
				bGuardarEnIdentificador = FALSO;
				switch(c)
				{
				case ' ':
					fprintf(pArchivoDestino, " ");
					break;
				case '\t':
					break;
				case '\n':
					fprintf(pArchivoDestino, "<br>\n");
					break;
				}
			}
			else
			if( c == '\"')
			{
				bGuardarEnIdentificador = FALSO;
				estado = ENCADENA;
			}
			else   /* saltar a estado entrada division, puede que le siga un asterisco(*) y que sea un comentario */
			if( c == '/' )
			{
				bGuardarEnIdentificador = FALSO;
				estado = ENDIVISION;
			}
			else
			if( c == '>' )
			{
				bGuardarEnIdentificador = FALSO;
				estado = ENCOMPMAY;
			}
			else
			if( c == '<' )
			{
				bGuardarEnIdentificador = FALSO;
				estado = ENCOMPMEN;
			}
			else
			if( c == '=' )
			{
				bGuardarEnIdentificador = FALSO;
				estado = ENIGUALDAD;
			}
			else
			if( c == '&' )
			{
				bGuardarEnIdentificador = FALSO;
				estado = ENAND;
			}
			else
			if( c == '|' )
			{
				bGuardarEnIdentificador = FALSO;
				estado = ENOR;
			}
			else
			{
				estado = HECHO;
				
				switch(c)
				{
				case EOF:
					bGuardarEnIdentificador = FALSO;
					lexemaActual.lexema = FINDEARCHIVO;
					break;
					
				case '+':
					lexemaActual.lexema = MAS;
					break;
					
				case '-':
					lexemaActual.lexema = MENOS;
					break;
					
				case '*':
					lexemaActual.lexema = POR;
					break;

				case ')':
					lexemaActual.lexema = PAREN_DER;
					break;
					
				case '(':
					lexemaActual.lexema = PAREN_IZQ;
					break;
					
				case '[':
					lexemaActual.lexema = PARENTESISCUADRADO_IZQ;
					break;
					
				case ']':
					lexemaActual.lexema = PARENTESISCUADRADO_DER;
					break;
					
				case '}':
					lexemaActual.lexema = LLAVE_DER;
					break;
					
				case '{':
					lexemaActual.lexema = LLAVE_IZQ;
					break;
					
				case ',':
					lexemaActual.lexema = OPERADOR_COMA;
					break;
					
				case ';':
					lexemaActual.lexema = PUNTOYCOMA;
					break;
					
				case ':':
					lexemaActual.lexema = DOSPUNTOS;
					break;
					
				default:
					lexemaActual.lexema = ERROR;
					fprintf(pArchivoDestino, "\nError:Simbolo desconocido");
					
				} /* fin del switch interno */
				
			} /*fin del else */
			break;
			
		case ENOR:
			bGuardarEnIdentificador = FALSO;
			if( c == '|' ) {
				lexemaActual.lexema = OR;
				estado = HECHO;
			}
			else {
				lexemaActual.lexema = ERROR;
				estado = HECHO;
			}
			break;
			
		case ENAND:
			bGuardarEnIdentificador = FALSO;
			if( c == '&' ) {
				lexemaActual.lexema = AND;
				estado = HECHO;
			}
			else {
				lexemaActual.lexema = ERROR;
				estado = HECHO;
			}
			break;
			
		case ENIGUALDAD:
			bGuardarEnIdentificador = FALSO;
			if( c == '=') {
				lexemaActual.lexema = IGUALQUE;
				estado = HECHO;
			}
			else
			{
				lexemaActual.lexema = ASIGNACION;
				estado = HECHO;
				deshacerCaracter();
			}
			break;
			
		case ENCOMPMEN:
			bGuardarEnIdentificador = FALSO;
			if( c == '=' ) {
				lexemaActual.lexema = MEN_IQUE;
				estado = HECHO;
			}
			else
			if( c == '>' ) {
				lexemaActual.lexema = DIFERENTE;
				estado = HECHO;
			}
			else {
				lexemaActual.lexema = MENORQUE;
				estado = HECHO;
				deshacerCaracter();
			}
			break;
			
		case ENCOMPMAY:
			bGuardarEnIdentificador = FALSO;
			if( c == '=') {
				lexemaActual.lexema = MA_IQUE;
				estado = HECHO;
			}
			else {
				lexemaActual.lexema = MAYORQUE;
				estado = HECHO;
				deshacerCaracter();
			}
			break;
			
		case ENDIVISION:
			bGuardarEnIdentificador = FALSO;
			if( c == '*') {
				estado = ENTRADACOMENT1;
				fprintf(pArchivoDestino, "<span class=\"nohemi-comentario\">/*");
			}
			else
			if( c == '/') {
				estado = ENTRADACOMENTLIN;
				fprintf(pArchivoDestino, "<span class=\"nohemi-comentario\">//");
			}
			else {
				lexemaActual.lexema = ENTRE;
				estado = HECHO;
				deshacerCaracter();
			}
			break;
		case ENTRADACOMENTLIN:
			bGuardarEnIdentificador = FALSO;
			if( c == '\n' ) {
				estado = INICIO;
				fprintf(pArchivoDestino, "</span><br>");
			}
			else {
				estado = ENTRADACOMENTLIN;
				fprintf(pArchivoDestino, "%c", c);
			}
			break;
			
		case ENTRADACOMENT1:
			bGuardarEnIdentificador = FALSO;
			if( c == '*' )
			estado = ENTRADACOMENT2;
			else
			estado = ENTRADACOMENT1;
			fprintf(pArchivoDestino, "%c", c);
			break;
			
		case ENTRADACOMENT2:
			bGuardarEnIdentificador = FALSO;
			
			fprintf(pArchivoDestino, "%c", c);
			
			if( c == '/')
			{
				fprintf(pArchivoDestino, "</span><br>");
				estado = INICIO;
			}
			else
			if( c == '*')
			estado = ENTRADACOMENT2;
			else
			estado = ENTRADACOMENT1;
			break;
			
			/* Reconoce numeros en entero, entero con signo, entero sin signo
		octal, octal sin signo, octal con signo, flotantes simples y en notacion científica*/
		case ENTRADANUMTIPOESTADO1:
			if( isdigit(c))
			estado = ENTRADANUMTIPOESTADO1;
			else
			if( c == 'e' || c == 'E')
			estado = ENTRADANUMTIPOESTADO6;
			else
			if( c == 'U' )
			estado = ENTRADANUMTIPOESTADO2;
			else
			{
				estado = HECHO;
				bGuardarEnIdentificador = FALSO;
				deshacerCaracter();
			}
			break;
			
		case ENTRADANUMTIPOESTADO2:
			if( c == 'L' )
			estado = ENTRADANUMTIPOESTADO3;
			else
			{
				estado = HECHO;
				bGuardarEnIdentificador = FALSO;
				deshacerCaracter();
			}
			break;
			
		case ENTRADANUMTIPOESTADO3:
			estado = HECHO;
			bGuardarEnIdentificador = FALSO;
			lexemaActual.lexema = IDNUM;
			deshacerCaracter();
			break;
			
		case ENTRADANUMTIPOESTADO4:
			if( isdigit(c) ){
				estado = ENTRADANUMTIPOESTADO5;
				lexemaActual.lexema = IDNUM;
			}
			else
			{
				estado = HECHO;
				bGuardarEnIdentificador = FALSO;
				lexemaActual.lexema = IDNUM;
				deshacerCaracter();
			}
			break;
			
		case ENTRADANUMTIPOESTADO5:
			if( isdigit(c) ){
				estado = ENTRADANUMTIPOESTADO5;
				lexemaActual.lexema = IDNUM;
			}
			else
			if( c == 'e' || c == 'E' ){
				estado = ENTRADANUMTIPOESTADO6;
				lexemaActual.lexema = IDNUM;
			}
			else
			{
				estado = HECHO;
				bGuardarEnIdentificador = FALSO;
				lexemaActual.lexema = IDNUM;
				deshacerCaracter();
			}
			break;
			
		case ENTRADANUMTIPOESTADO6:
			if( c == '+' || c == '-' ){
				estado = ENTRADANUMTIPOESTADO7;
				lexemaActual.lexema = IDNUM;
			}
			else
			{
				
				bGuardarEnIdentificador = FALSO;
				lexemaActual.lexema = ERROR;
				estado = HECHO;
				deshacerCaracter();
			}
			break;
			
		case ENTRADANUMTIPOESTADO7:
			if( isdigit(c) ){
				estado = ENTRADANUMTIPOESTADO8;
				lexemaActual.lexema = IDNUM;
			}
			else
			{
				
				bGuardarEnIdentificador = FALSO;
				lexemaActual.lexema = ERROR;
				estado = HECHO;
				deshacerCaracter();
			}
			break;
			
		case ENTRADANUMTIPOESTADO8:
			if( isdigit(c) ){
				estado = ENTRADANUMTIPOESTADO8;
				lexemaActual.lexema = IDNUM;
			}
			else
			{
				estado = HECHO;
				bGuardarEnIdentificador = FALSO;
				lexemaActual.lexema = IDNUM;
				deshacerCaracter();
			}
			break;
			
		case ENTRADANUMTIPOESTADO9:
			if( isdigit(c) ){
				estado = ENTRADANUMTIPOESTADO11;
			}
			else
			if( c == 'x' || c == 'X' ){
				estado = ENTRADANUMTIPOESTADO10;
			}
			else
			{
				estado = HECHO;
				bGuardarEnIdentificador = FALSO;
				deshacerCaracter();
			}
			break;
			
		case ENTRADANUMTIPOESTADO10:
			if( isdigit(c) ){
				estado = ENTRADANUMTIPOESTADO14;
			}
			else
			{
				
				bGuardarEnIdentificador = FALSO;
				lexemaActual.lexema = ERROR;
				estado = HECHO;
				deshacerCaracter();
			}
			break;
			
		case ENTRADANUMTIPOESTADO11:
			if( isdigit(c) ){
				estado = ENTRADANUMTIPOESTADO11;
			}
			else
			if( c == 'L' ){
				estado = ENTRADANUMTIPOESTADO12;
			}
			else
			if( c == 'U' ){
				estado = ENTRADANUMTIPOESTADO13;
			}
			else
			{
				estado = HECHO;
				bGuardarEnIdentificador = FALSO;
				deshacerCaracter();
			}
			break;
			
		case ENTRADANUMTIPOESTADO12:
			estado = HECHO;
			bGuardarEnIdentificador = FALSO;
			lexemaActual.lexema = IDNUM;
			deshacerCaracter();
			break;
			
		case ENTRADANUMTIPOESTADO13:
			estado = HECHO;
			bGuardarEnIdentificador = FALSO;
			lexemaActual.lexema = IDNUM;
			deshacerCaracter();
			break;
			
		case ENTRADANUMTIPOESTADO14:
			if( isdigit(c) ){
				estado = ENTRADANUMTIPOESTADO14;
			}
			else
			if( c == 'L' ){
				estado = ENTRADANUMTIPOESTADO15;
			}
			else
			if( c == 'U' ){
				estado = ENTRADANUMTIPOESTADO16;
			}
			break;
			
		case ENTRADANUMTIPOESTADO15:
			{
				estado = HECHO;
				bGuardarEnIdentificador = FALSO;
				deshacerCaracter();
			}
			break;
			
		case ENTRADANUMTIPOESTADO16:
			if( c == 'L' ){
				estado = ENTRADANUMTIPOESTADO17;
				lexemaActual.lexema = IDNUM;
			}
			else
			{
				estado = HECHO;
				bGuardarEnIdentificador = FALSO;
				lexemaActual.lexema = IDNUM;
				deshacerCaracter();
			}
			break;
			
		case ENTRADANUMTIPOESTADO17:
			{
				estado = HECHO;
				bGuardarEnIdentificador = FALSO;
				lexemaActual.lexema = IDNUM;
				deshacerCaracter();
			}
			break;
			
		case ENID:
			if( (!isalpha(c)) && (c != '_') && (!isdigit(c)) )
			{
				estado = HECHO;
				bGuardarEnIdentificador = FALSO;
				deshacerCaracter();
				lexemaActual.lexema = ID;
			}
			break;
			
		case ENCADENA:
			lexemaActual.lexema = IDCADENA;
			bGuardarEnIdentificador = VERDADERO;
			
			if( c == '\"')
			{
				estado = HECHO;
				bGuardarEnIdentificador = FALSO;
			}
			else
			estado = ENCADENA;
			break;
			
		case HECHO:
			break;
			
		default: /* nunca deberia de ocurrir */
			fprintf(pArchivoDestino, "\nBug en escaneo o analisis lexico\n");
			estado = HECHO;
			lexemaActual.lexema = ERROR;
			Error = VERDADERO;
			
		} /* fin del switch externo */
		
		if( (bGuardarEnIdentificador) && (indiceCadenaLexema <= MAXIMALONGITUDDELEXEMA))
		cadenaDeLexema[indiceCadenaLexema++]=c;
		
		if( estado == HECHO)
		{
			cadenaDeLexema[indiceCadenaLexema] = '\0';
			
			if( lexemaActual.lexema == ID)
			{
				lexemaActual.lexema = buscarPalabraReservada(cadenaDeLexema);
			}
			
			if( cadenaDeLexema != NULL || strlen(cadenaDeLexema) != 0)
			{   
				switch( lexemaActual.lexema )
				{
					
				case ASIGNACION:
					strcpy(lexemaActual.informacion, "=");
					break;
					
				case MENORQUE:
					strcpy(lexemaActual.informacion, "<");
					break;
					
				case MAYORQUE:
					strcpy(lexemaActual.informacion, ">");
					break;
					
				case IGUALQUE:
					strcpy(lexemaActual.informacion, "==");
					break;
					
				case DIFERENTE:
					strcpy(lexemaActual.informacion, "!=");
					break;
					
				case MA_IQUE:
					strcpy(lexemaActual.informacion, ">=");
					break;
				case MEN_IQUE:
					strcpy(lexemaActual.informacion, "<=");
					break;
				default:
					strcpy(lexemaActual.informacion, cadenaDeLexema);
				}
			}
			lexemaActual.lineanumero = lineanumero;
		}
		
	} /* fin del while */

	if(imprimeAnalisisLexico)
	{
		// fprintf(pArchivoDestino, "<br>\n");
		imprimirLexema(lexemaActual.lexema, cadenaDeLexema);
		// listaDeAnalisis = construirListaDeAnalisis(lexemaActual.lexema, cadenaDeLexema);
	}
	
	return lexemaActual;

} /* fin de la funcion obtenerLexema */    
