/* anasin.c */
/**************************************************************
**    Proyecto Personal                                    **
**    Compilador HAMAT JAVAC                               **
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
#include "globales.h"
#include "utiles.h"
#include "analex.h"
#include "anasin.h"
#include <stdio.h> // nota: declaracion de prueba
static TipoLexema lexema; /* mantiene el token actual */ // nota: esta variable no se esta usando
static NodoListaLexema *lista; /* mantiene el token actual con información completa */
/*
	prototipo de funciones recursivas para los arboles de las reglas
	gramaticales del lenguaje nohemi
*/
static NodoArbol *programa( void );
static NodoArbol *lista_declaracion( void );
static NodoArbol *declaracion( void );
static int esTipoVariable(TipoLexema lexema);
static NodoArbol *variable_declaracion( void );
static NodoArbol *tipo_variable( void );
static NodoArbol *funcion_declaracion( void );
static NodoArbol *procedimiento_declaracion( void );
static NodoArbol *cuerpo_clase( void );
static NodoArbol *clase_declaracion( void );
static NodoArbol *parametros( void );
static NodoArbol *lista_parametros( void );
static NodoArbol *parametro( void );
static NodoArbol *cuerpo_clase( void );
static NodoArbol *sentencia_compuesta( void );
static NodoArbol *declaracion_local( void );
static NodoArbol *lista_sentencia( void );
static NodoArbol *sentencia( void );
static NodoArbol *expresion_sentencia( void );
static NodoArbol *expresion( void );
static NodoArbol *expresion_simple( void );
static NodoArbol *si_sentencia( void );
static NodoArbol *seleccionar_sentencia();
static NodoArbol *alcontrario_sentencia( void );
static NodoArbol *lista_caso_sentencia( void );
static NodoArbol *caso_sentencia( void );
static NodoArbol *repetir_sentencia( void );
static NodoArbol *para_sentencia( void );
static NodoArbol *mientras_sentencia( void );
static NodoArbol *retornar_sentencia( void );
static NodoArbol *expresion_comparacion( void );
static NodoArbol *expresion_simple( void );
static NodoArbol *expresion_aditiva( void );
static NodoArbol *termino( void );
static NodoArbol *variable( void );
static NodoArbol *factor( void );
static NodoArbol *llamada( void );
static NodoArbol *argumentos( void );
static NodoArbol *lista_argumentos( void );

NodoArbol *analizarSintaxis( NodoListaLexema *listaLex );

/* funciones para analizar sintacticamente una funcion */
static void errorSintactico( char *mensaje )
{
	fprintf(pArchivoDestino, "\n>>>");
	fprintf(pArchivoDestino, "Error sintactico en la linea %d: %s", lista->informacionLexema.lineanumero, mensaje);
	Error = VERDADERO;
} /* fin de la funcion errorSintactico */

static void parearCompleto(TipoLexema espectativa)
{
	
	if( lista->informacionLexema.lexema == espectativa)
	lista=lista->siguiente;
	else
	{
		errorSintactico("lexema inaceptable--> ");
		imprimirLexema(lista->informacionLexema.lexema, lista->informacionLexema.informacion);
		fprintf(pArchivoDestino, "      ");
		Error = VERDADERO;
	}
	
}

/* Parte principal de programa, aqui invocamos los reconocerderes,
programa() seria la primer parte del lenguaje
*/
static NodoArbol *programa( void )
{
	// Creamos el arbol para sentencia
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_PROGRAMA), *p=NULL;
	fprintf(pArchivoAnaSin, "\nPROGRAMA -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	// como es la primera parte, todo programa tiene que contener la palabra programa
	parearCompleto(PROGRAMA);
	// en el arbol temporal creamos el nombre de la informacion que tiene la tabla de símbolos lista
	temporal->atributo.nombre = lista->informacionLexema.informacion;
	
	// No guardamos informaciòn del identificador de la funciòn y la hacemos coincidir
	parearCompleto(ID);
	// hacemos coincidir con punto y coma
	parearCompleto(PUNTOYCOMA);
	
	// Se logró reservar memoria
	if( temporal != NULL)
	{
		// hijo de programa seran la lista de declaraciones
		temporal->hijo[0]=lista_declaracion();
	}
	
	
	return temporal;
} /* fin de funcion programa_sentencia */

/* Lista de declaraciones contiene la lista de posibles declaraciones de variables
ejemplo entero a; entero b; real x;
*/
static NodoArbol *lista_declaracion( void )
{
	NodoArbol *temporal = declaracion();
	NodoArbol *p = temporal;
	fprintf(pArchivoAnaSin, "LISTA-DECLARACION -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	/* El último nodo de la lista es el final de la lista de lexemas. */
	while( lista->informacionLexema.lexema != FINDEARCHIVO )
	{
		NodoArbol *q;
		q = declaracion();
		if( q != NULL)
		{
			if( temporal != NULL)
			temporal = p = q;
			else
			{
				p->hijoextra = q;
				p=q;
			}
		}
	}
	
	return temporal;
}

static NodoArbol *declaracion( void )
{
	NodoArbol *temporal = NULL;
	
	fprintf(pArchivoAnaSin, "DECLARACION -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	if( lista->informacionLexema.lexema == CLASE )
	{
		temporal = clase_declaracion();
	}
	else
	if( lista->informacionLexema.lexema == PROCEDIMIENTO )
	{
		temporal = procedimiento_declaracion();
	}
	else
	/* la declaracion es una variable */
	if( ( esTipoVariable(lista->informacionLexema.lexema) &&
				lista->siguiente->informacionLexema.lexema == ID &&
				lista->siguiente->siguiente->informacionLexema.lexema == PUNTOYCOMA) 
			||
			( esTipoVariable(lista->informacionLexema.lexema) &&
				lista->siguiente->informacionLexema.lexema == ID &&
				lista->siguiente->siguiente->informacionLexema.lexema == PARENTESISCUADRADO_IZQ))
	{
		temporal = variable_declaracion();
	}
	else
	if( esTipoVariable(lista->informacionLexema.lexema) &&
			lista->siguiente->informacionLexema.lexema == ID &&
			lista->siguiente->siguiente->informacionLexema.lexema == PAREN_IZQ )
	{
		temporal  = funcion_declaracion();
	}
	else
	if( lista->informacionLexema.lexema == FINDEARCHIVO )
	{
		/* Se ha encontrado FINDEARCHIVO, no hay mas hijos */
		temporal = NULL;
		return temporal;
	}
	
	return temporal;
} /* fin de funcion declaracion */

/* nota: no implementado
static lista_variables( void )
{
	
}
*/
/* Esta funcion es para averiguar si el lexema es un tipo de variable
para esto se han considerado cuatro casos: ENTERO, CADENA, REAL y CARACTER */
static int esTipoVariable(TipoLexema lexema)
{
	int resultado=FALSO;
	
	switch(lexema)
	{
	case ENTERO:
	case CADENA:
	case REAL:
	case CARACTER:
		resultado = VERDADERO;
		break;
	}
	
	return resultado;
	
}


static NodoArbol *variable_declaracion( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_DECLARACION_GLOBAL), *p;
	fprintf(pArchivoAnaSin, "VARIABLE-DECLARACION -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	/* Invocamos para ambos casos el tipo de variable que se va a declarar. */
	if(temporal != NULL)
	temporal->hijo[0] = tipo_variable();
	
	parearCompleto(ID);
	if( lista->informacionLexema.lexema == PARENTESISCUADRADO_IZQ)
	{
		parearCompleto(PARENTESISCUADRADO_IZQ);
		parearCompleto(IDNUM);
		parearCompleto(PARENTESISCUADRADO_DER);
	}
	parearCompleto(PUNTOYCOMA);
	
	return temporal;
}

static NodoArbol *tipo_variable( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_TIPO_VARIABLE), *p;
	
	fprintf(pArchivoAnaSin, "TIPO-VARIABLE -->");
	fprintf(pArchivoAnaSin, "%s\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	sprintf(temporal->nombre, "%s", lista->informacionLexema.informacion); 
	switch(lista->informacionLexema.lexema)
	{
	case REAL:
		parearCompleto(REAL);
		temporal->type = Real;
		break;
	case ENTERO:
		parearCompleto(ENTERO);
		temporal->type = Entero;
		break;
	case CARACTER:
		parearCompleto(CARACTER);
		temporal->type = Caracter;
		break;
	case CADENA:
		parearCompleto(CADENA);
		temporal->type = Cadena;
		break;
	}
	
	return temporal;
}

static NodoArbol *funcion_declaracion( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_FUNCION), *p;
	fprintf(pArchivoAnaSin, "FUNCION-DECLARACION -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	
	temporal->hijo[0] = tipo_variable();
	
	// Colocar el nombre de la funcion para que aparezca en el árbol
	temporal->atributo.nombre = lista->informacionLexema.informacion;
	
	parearCompleto(ID);
	
	parearCompleto( PAREN_IZQ );
	temporal->hijo[1] = parametros();
	parearCompleto( PAREN_DER );
	
	temporal->hijo[2] = sentencia_compuesta();
	
	return temporal;
}

static NodoArbol *procedimiento_declaracion( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_PROCEDIMIENTO);
	fprintf(pArchivoAnaSin, "PROCEDIMIENTO-DECLARACION -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	parearCompleto(PROCEDIMIENTO);
	
	temporal->atributo.nombre = lista->informacionLexema.informacion;
	
	if( lista->informacionLexema.lexema == ID &&
			lista->siguiente->informacionLexema.lexema == LLAVE_IZQ )
	{
		// nota: temporal.nombre = lista->informacionLexema.informacion;
		parearCompleto(ID);
		temporal->hijo[0] = sentencia_compuesta();
	}
	else
	if( lista->informacionLexema.lexema == ID &&
			lista->siguiente->informacionLexema.lexema == PAREN_IZQ )
	{
		// nota: temporal.nombre = lista->informacionLexema.informacion;
		parearCompleto(ID);
		parearCompleto(PAREN_IZQ);
		temporal->hijo[0] = parametros();
		parearCompleto(PAREN_DER);
		temporal->hijo[1] = sentencia_compuesta();
	}
	
	return temporal;
}

static NodoArbol *clase_declaracion( void )
{
	NodoArbol *temporal = NULL;
	fprintf(pArchivoAnaSin, "CLASE-DECLARACION -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	parearCompleto(CLASE);
	temporal->atributo.tipoLexemaOperador = lista->informacionLexema.lexema;
	
	parearCompleto(ID);
	parearCompleto(LLAVE_IZQ);
	
	temporal = lista_declaracion();
	
	parearCompleto(LLAVE_DER);
	
	return temporal;
}
// nota: esta clase ya no se invoca...
// no tiene iteracción durante el programa
static NodoArbol *cuerpo_clase( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_CLASE);
	fprintf(pArchivoAnaSin, "CUERPO-CLASE -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	temporal->hijo[0] = lista_declaracion();
	
	return temporal;
}

static NodoArbol *parametros( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_PARAMETROS);
	
	
	fprintf(pArchivoAnaSin, "PARAMETROS -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	if( lista != NULL )
	if( lista->informacionLexema.lexema == PAREN_DER )
	temporal->hijo[0] = NULL;
	else
	temporal->hijo[0] = lista_parametros();
	
	
	return temporal;
}

static NodoArbol *lista_parametros( void )
{
	NodoArbol *temporal=parametro();
	NodoArbol *p = temporal;
	
	fprintf(pArchivoAnaSin, "LISTA-PARAMETROS -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	if( lista->informacionLexema.lexema == OPERADOR_COMA)
	parearCompleto(OPERADOR_COMA);
	
	while( lista->informacionLexema.lexema != PAREN_DER)
	{
		NodoArbol *q;
		
		q = parametro();
		if( lista->informacionLexema.lexema == OPERADOR_COMA)
		parearCompleto(OPERADOR_COMA);
		
		if( q != NULL )
		{
			if( temporal == NULL)
			temporal = p = q;
			else /* en este instante p no puede ser null */
			{
				p->hijoextra = q;
				p = q;
			}
		}
		
		
	} /* fin del while */
	
	return temporal;
}

static NodoArbol *parametro( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_PARAMETRO);
	fprintf(pArchivoAnaSin, "PARAMETRO -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	temporal->hijo[0] = tipo_variable();
	
	sprintf(temporal->nombre, "%s", lista->informacionLexema.informacion);
	
	parearCompleto(ID);
	if( lista->informacionLexema.lexema == PARENTESISCUADRADO_IZQ)
	{
		parearCompleto(PARENTESISCUADRADO_IZQ);
		parearCompleto(PARENTESISCUADRADO_DER);
	}
	
	return temporal;
}

static NodoArbol *sentencia_compuesta( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_COMPUESTA), *p=NULL;
	fprintf(pArchivoAnaSin, "SENTENCIA-COMPUESTA -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	if( temporal != NULL )
	{
		parearCompleto(LLAVE_IZQ);
		
		/* Identificar todas las declaraciones de variables */
		while( ((  lista->informacionLexema.lexema == ENTERO ||
		lista->informacionLexema.lexema == REAL ||
		lista->informacionLexema.lexema == CADENA ||
		lista->informacionLexema.lexema == CARACTER) &&
		lista->siguiente->informacionLexema.lexema == ID &&
		lista->siguiente->siguiente->informacionLexema.lexema == PUNTOYCOMA) 
		||
		((  lista->informacionLexema.lexema == ENTERO ||
		lista->informacionLexema.lexema == REAL ||
		lista->informacionLexema.lexema == CADENA ||
		lista->informacionLexema.lexema == CARACTER) &&
		lista->siguiente->informacionLexema.lexema == ID &&
		lista->siguiente->siguiente->informacionLexema.lexema == PARENTESISCUADRADO_IZQ))
		{
			p = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_VAR);
			
			p->hijo[0]=declaracion_local();
			
			p->siguiente = temporal;
			temporal = p;
		} /* fin de sentencia while */
		
		temporal->hijo[1] = lista_sentencia();
		
		parearCompleto(LLAVE_DER);
	}
	
	return temporal;
}

static NodoArbol *declaracion_local( void )
{
	NodoArbol *temporal = variable_declaracion();
	NodoArbol *p = temporal;
	
	fprintf(pArchivoAnaSin, "DECLARACION-LOCAL -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	while( (lista->informacionLexema.lexema == ENTERO ||
	lista->informacionLexema.lexema == REAL ||
	lista->informacionLexema.lexema == CARACTER ||
	lista->informacionLexema.lexema == CADENA) &&
	lista->siguiente->informacionLexema.lexema == ID && 
	lista->siguiente->siguiente->informacionLexema.lexema == PUNTOYCOMA)
	{
		NodoArbol *q;
		
		q = variable_declaracion();
		if( lista->informacionLexema.lexema == OPERADOR_COMA)
		parearCompleto(OPERADOR_COMA);
		
		if( q != NULL )
		{
			if( temporal == NULL)
			temporal = p = q;
			else /* en este instante p no puede ser null */
			{
				p->hijoextra = q;
				p = q;
			}
		}
		
		
	} /* fin del while */
	
	return temporal;
}

static NodoArbol *lista_sentencia( void )
{
	NodoArbol *temporal = sentencia();
	NodoArbol *p = temporal;
	
	fprintf(pArchivoAnaSin, "LISTA-SENTENCIA -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);   
	
	while(  
	lista != NULL &&
	lista->informacionLexema.lexema != LLAVE_DER &&
	lista->informacionLexema.lexema != SINO &&
	lista->informacionLexema.lexema != REPETIR &&
	lista->informacionLexema.lexema != INTERRUMPIR
	) 
	{
		NodoArbol *q;
		
		q = sentencia();
		
		if( q != NULL )
		{
			if( temporal == NULL)
			temporal = p = q;
			else /* en este instante p no puede ser null */
			{
				p->hijoextra = q;
				p = q;
			}
		}
		
	} /* fin del while */
	
	return temporal;
} /* fin de la funcion lista_sentencia */

static NodoArbol *sentencia( void )
{
	NodoArbol *temporal = NULL;
	
	fprintf(pArchivoAnaSin, "SENTENCIA -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	switch( lista->informacionLexema.lexema )
	{
	case SI:
		temporal = si_sentencia();
		break;

	case SELECCIONAR:
		temporal = seleccionar_sentencia();
		break;
		
	case REPETIR:
		temporal = repetir_sentencia();
		break;

	case PARA:
		temporal = para_sentencia();
		break;

	case MIENTRAS:
		temporal = mientras_sentencia();
		break;
		
	case RETORNAR:
		temporal = retornar_sentencia();
		break;
		
	case LLAVE_IZQ:
		temporal = sentencia_compuesta();
		break;

	default:
		temporal = expresion_sentencia();
		break;
		
	} /* fin del switch */

	return temporal;

} /* fin de la funcion sentencia */

static NodoArbol *expresion_sentencia( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_EXPRESION_SENTENCIA);
	
	fprintf(pArchivoAnaSin, "EXPRESION-SENTENCIA -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	if( lista->informacionLexema.lexema == PUNTOYCOMA )
	parearCompleto(PUNTOYCOMA);
	else
	{
		temporal->hijo[0] = expresion();
		parearCompleto(PUNTOYCOMA);
	}
	
	return temporal;
}

static NodoArbol *expresion( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_EXPRESION);
	
	fprintf(pArchivoAnaSin, "EXPRESION -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	if(
			/* reconocer una asignacion a una variable simple: ID = */
			(   lista->informacionLexema.lexema == ID && 
				lista->siguiente->informacionLexema.lexema== ASIGNACION ) ||
			/* o reconoce una asignacion a un arreglo simple: ID[IDNUM] = */
			(   lista->informacionLexema.lexema == ID &&
				lista->siguiente->informacionLexema.lexema == PARENTESISCUADRADO_IZQ) )
	{
		temporal->hijo[0] = variable();
		if( lista->informacionLexema.lexema == ASIGNACION)
		{
			parearCompleto(ASIGNACION);
			temporal->hijo[1] = expresion();
		}
	}
	else
	temporal->hijo[0] = expresion_simple();
	
	return temporal;
}

static NodoArbol *variable( void )
{
	NodoArbol *temporal =  nuevoNodoExpresion(TIPOARBOL_VARIABLE);
	
	fprintf(pArchivoAnaSin, "VARIABLE -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	temporal->hijo[0] = NULL;
	temporal->atributo.nombre = lista->informacionLexema.informacion;

	parearCompleto(ID);
	if( lista->informacionLexema.lexema == PARENTESISCUADRADO_IZQ)
	{
		parearCompleto(PARENTESISCUADRADO_IZQ);
		temporal->hijo[0] = expresion();
		parearCompleto(PARENTESISCUADRADO_DER);
	}
	return temporal;
}

static NodoArbol *expresion_simple( void )
{
	NodoArbol *temporal = expresion_comparacion();
	
	fprintf(pArchivoAnaSin, "EXPRESION-SIMPLE -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	while( lista->informacionLexema.lexema == AND || lista->informacionLexema.lexema == OR)
	{
		NodoArbol *auxtemporal = nuevoNodoExpresion(TIPOARBOL_OPERADOR);
		
		if( auxtemporal != NULL )
		{
			auxtemporal->hijo[0] = temporal;
			auxtemporal->atributo.tipoLexemaOperador = lista->informacionLexema.lexema;
			temporal = auxtemporal;
			parearCompleto(lista->informacionLexema.lexema); // nota: esto podria causar un error 
			temporal->hijo[1]= expresion_comparacion();
		}
	}
	return temporal;
}

static NodoArbol *si_sentencia( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SI_SENTENCIA);
	
	fprintf(pArchivoAnaSin, "SELECCION-SENTENCIA -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	parearCompleto(SI);

	parearCompleto(PAREN_IZQ);

	if( temporal != NULL )
	temporal->hijo[0] = expresion_simple();
	
	parearCompleto(PAREN_DER);

	if( temporal != NULL )
	temporal->hijo[1] = lista_sentencia();
	
	if( lista->informacionLexema.lexema == SINO )
	{
		parearCompleto(SINO);
		temporal->hijo[2] = lista_sentencia();
	}

	return temporal;
} /* fin de funcion si_sentencia */

static NodoArbol *seleccionar_sentencia(void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_SELECCIONAR);
	
	
	fprintf(pArchivoAnaSin, "SENTENCIA-SELECCIONAR -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	
	parearCompleto(SELECCIONAR);
	parearCompleto(PAREN_IZQ);

	temporal->hijo[0] = expresion_simple();

	parearCompleto(PAREN_DER);
	parearCompleto(LLAVE_IZQ);

	temporal->hijo[1] = lista_caso_sentencia();
	
	if(lista->informacionLexema.lexema == ALCONTRARIO ){
		temporal->hijo[2] = alcontrario_sentencia();
		
	}
	

	parearCompleto(LLAVE_DER);

	return temporal;

}

static NodoArbol *alcontrario_sentencia( void ) {
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_ALCONTRARIO);
	int pareja = FALSO;

	fprintf(pArchivoAnaSin, "ALCONTRARIO-SENTENCIA -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	parearCompleto(ALCONTRARIO);
	parearCompleto(DOSPUNTOS);
	if(lista->informacionLexema.lexema == LLAVE_IZQ) {
		parearCompleto(LLAVE_IZQ);
		pareja = VERDADERO;
	}
	temporal->hijo[0] = lista_sentencia();
	if(pareja == VERDADERO);
	parearCompleto(LLAVE_DER);

	return temporal;
	
}

static NodoArbol *lista_caso_sentencia( void ) {
	NodoArbol *temporal = caso_sentencia();
	NodoArbol *p = temporal;
	
	fprintf(pArchivoAnaSin, "LISTA-CASO-SENTENCIA -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);   
	
	while( lista->informacionLexema.lexema != LLAVE_DER 
	&& lista->informacionLexema.lexema != ALCONTRARIO)
	{
		NodoArbol *q;
		
		q = caso_sentencia();
		
		if( q != NULL )
		{
			if( temporal == NULL)
			temporal = p = q;
			else /* en este instante p no puede ser null */
			{
				p->hijoextra = q;
				p = q;
			}
		}
		
	} /* fin del while */
	
	return temporal;
}

static NodoArbol *caso_sentencia( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_CASO_SENTENCIA);
	int pareja = FALSO;
	
	

	fprintf(pArchivoAnaSin, "CASO-SENTENCIA -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	parearCompleto(CASO);
	temporal->hijo[0] = expresion_simple();
	
	if( ( temporal != NULL ) && ( lista->informacionLexema.lexema == IDNUM ) )
	temporal->atributo.val = atoi(cadenaDeLexema);

	parearCompleto(DOSPUNTOS);

	if(lista->informacionLexema.lexema == LLAVE_IZQ) {
		parearCompleto(LLAVE_IZQ);
		pareja = VERDADERO;
	}
	
	if( temporal != NULL )
	temporal->hijo[1] = lista_sentencia();

	if(pareja == VERDADERO)
	parearCompleto(LLAVE_DER);
	
	if(lista->informacionLexema.lexema == INTERRUMPIR); {
		parearCompleto(INTERRUMPIR);
		parearCompleto(PUNTOYCOMA);
	}

	return temporal;
}

static NodoArbol *repetir_sentencia( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_REPETIR);
	
	fprintf(pArchivoAnaSin, "REPETIR-SENTENCIA -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	parearCompleto(REPETIR);

	if( temporal != NULL)
	temporal->hijo[0] = lista_sentencia();
	
	parearCompleto(HASTA);

	if( temporal != NULL)
	temporal->hijo[1] = expresion_simple();

	return temporal;
}

static NodoArbol *para_sentencia( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_PARA);
	
	fprintf(pArchivoAnaSin, "PARA-SENTENCIA -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	parearCompleto(PARA);

	parearCompleto(PAREN_IZQ);
	if( temporal != NULL )
	temporal->hijo[0]= expresion();
	parearCompleto(PUNTOYCOMA);

	if( temporal != NULL )
	temporal->hijo[1] = expresion_simple();

	parearCompleto(PUNTOYCOMA);

	if( temporal != NULL )
	temporal->hijo[2] = expresion_simple();
	parearCompleto(PAREN_DER);

	if( temporal != NULL )
	temporal->hijo[3] = sentencia();
	
	return temporal;
} /* fin de la funcion para_sentencia */

static NodoArbol *mientras_sentencia( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_MIENTRAS);
	
	fprintf(pArchivoAnaSin, "ITERACION-SENTENCIA -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	parearCompleto(MIENTRAS);
	
	parearCompleto(PAREN_IZQ);
	if( temporal != NULL )
	temporal->hijo[0] = expresion_simple();
	parearCompleto(PAREN_DER);

	if( temporal != NULL && lista->informacionLexema.lexema == LLAVE_IZQ)
	temporal->hijo[1] = lista_sentencia();

	return temporal;
} /* fin de la funcion mientras_sentencia */

static NodoArbol *retornar_sentencia( void )
{
	NodoArbol *temporal = nuevoNodoSentencia(TIPOARBOL_SENTENCIA_RETORNAR);
	
	fprintf(pArchivoAnaSin, "RETORNAR-SENTENCIA -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	parearCompleto(RETORNAR);
	if( lista->informacionLexema.lexema == PUNTOYCOMA)
	parearCompleto(PUNTOYCOMA);
	else
	if( lista->informacionLexema.lexema == PAREN_IZQ)
	{
		parearCompleto(PAREN_IZQ);
		temporal->hijo[0] = expresion_simple();
		parearCompleto(PAREN_DER);
	}
	return temporal;
}

static NodoArbol *expresion_comparacion( void )
{
	NodoArbol *temporal = expresion_aditiva();

	fprintf(pArchivoAnaSin, "EXPRESION-COMPARACION -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	while(    ( lista->informacionLexema.lexema == IGUALQUE  ) 
	|| ( lista->informacionLexema.lexema == DIFERENTE )
	|| ( lista->informacionLexema.lexema == MENORQUE  ) 
	|| ( lista->informacionLexema.lexema == MAYORQUE  )
	|| ( lista->informacionLexema.lexema == MEN_IQUE  )
	|| ( lista->informacionLexema.lexema == MA_IQUE   )
	)
	{
		NodoArbol *auxtemporal = nuevoNodoExpresion(TIPOARBOL_OPERADOR);
		
		if( auxtemporal != NULL )
		{
			auxtemporal->hijo[0] = temporal;
			auxtemporal->atributo.tipoLexemaOperador = lista->informacionLexema.lexema;
			temporal = auxtemporal;
			parearCompleto(lista->informacionLexema.lexema); // nota: esto podria causar un error
			temporal->hijo[1] = expresion_aditiva();
		}
		
	} /* fin del while */

	return temporal;
} /* fin de la funcion expresion_comparacion */

static NodoArbol *expresion_aditiva( void )
{
	NodoArbol *temporal = termino();
	
	fprintf(pArchivoAnaSin, "EXPRESION-ADITIVA -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	while( ( lista->informacionLexema.lexema == MAS ) || ( lista->informacionLexema.lexema == MENOS ) )
	{
		NodoArbol *auxtemporal = nuevoNodoExpresion(TIPOARBOL_OPERADOR);

		if( auxtemporal != NULL )
		{
			auxtemporal->hijo[0] = temporal;
			auxtemporal->atributo.tipoLexemaOperador = lista->informacionLexema.lexema;
			temporal = auxtemporal;
			parearCompleto(lista->informacionLexema.lexema);
			temporal->hijo[1] = termino();
		} /* fin de if principal */

	} /* fin del while */

	return temporal;

} /* fin de la funcion expresion_simple */

static NodoArbol *termino( void )
{
	NodoArbol *temporal = factor();

	fprintf(pArchivoAnaSin, "TERMINO -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	while( ( lista->informacionLexema.lexema == POR ) || ( lista->informacionLexema.lexema == ENTRE ) )
	{
		NodoArbol *auxtemporal = nuevoNodoExpresion(TIPOARBOL_OPERADOR);
		
		if( auxtemporal != NULL )
		{
			auxtemporal->hijo[0] = temporal;
			auxtemporal->atributo.tipoLexemaOperador = lista->informacionLexema.lexema;
			temporal = auxtemporal;
			parearCompleto(lista->informacionLexema.lexema); /* nota: esto puede causar irregularidad de
			análisis de sintáxis */
			auxtemporal->hijo[1] = factor();
		}
		
	} /* fin del ciclo while */

	return temporal;

} /* fin de la funcion termino */

static NodoArbol *factor( void )
{
	NodoArbol *temporal = NULL;
	fprintf(pArchivoAnaSin, "FACTOR -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	/* nota: buscar todos los exit(0) */
	if( lista != NULL )
	{
		if( lista->informacionLexema.lexema == PAREN_IZQ )
		{
			parearCompleto(PAREN_IZQ);
			temporal = expresion();
			parearCompleto(PAREN_DER);
		}
		else
		if( lista->informacionLexema.lexema == ID && lista->siguiente->informacionLexema.lexema == PARENTESISCUADRADO_IZQ)
		{
			temporal = variable();
		}
		else
		if( lista->siguiente != NULL && lista->informacionLexema.lexema == ID && lista->siguiente->informacionLexema.lexema == PAREN_IZQ )
		{
			temporal = llamada();
		}
		else
		if( lista->informacionLexema.lexema == ID )
		{
			temporal = variable();
		}
		else
		if( lista->informacionLexema.lexema == IDNUM )
		{
			temporal = nuevoNodoExpresion(TIPOARBOL_CONSTANTE);
			
			if( ( temporal != NULL ) && ( lista->informacionLexema.lexema == IDNUM ) )
			temporal->atributo.val = atoi(lista->informacionLexema.informacion);
			parearCompleto(IDNUM);
		}
		else
		if( lista->informacionLexema.lexema == IDCADENA )
		{
			temporal = nuevoNodoExpresion(TIPOARBOL_CADENA);
			if( ( temporal != NULL ) && ( lista->informacionLexema.lexema == IDCADENA) )
			temporal->atributo.nombre = lista->informacionLexema.informacion; /*temporal->atributo.nombre = copiarCadena(cadenaDeLexema); */
			parearCompleto(IDCADENA);
		}
		else
		{
			errorSintactico("lexema inaceptable -> " );
			imprimirLexema(lista->informacionLexema.lexema, lista->informacionLexema.informacion);
			/* obtener siguiente lexema */
			lista=lista->siguiente;
		}
	} /* fin del if principal */
	
	return temporal;

} /* fin de la funcion factor */

static NodoArbol *llamada( void )
{
	NodoArbol *temporal = nuevoNodoExpresion(TIPOARBOL_LLAMADA);
	
	temporal->atributo.nombre = lista->informacionLexema.informacion;
	
	fprintf(pArchivoAnaSin, "LLAMADA -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	/*
	temporal->atributo.nombre = (char *)malloc(sizeof(char)*strlen(lista->informacionLexema.informacion));
	strcpy(temporal->atributo.nombre, lista->informacionLexema.informacion);
	temporal->atributo.tipoLexemaOperador = lista->informacionLexema.lexema;
	*/
	/* nota: eliminar todos los *p que no estan siendo utilizados */
	parearCompleto(ID);
	parearCompleto(PAREN_IZQ);
	
	temporal->hijo[0]=argumentos();
	
	parearCompleto(PAREN_DER);
	
	return temporal;
}

static NodoArbol *argumentos( void )
{
	NodoArbol *temporal =  nuevoNodoExpresion(TIPOARBOL_ARGUMENTOS), *p;
	
	temporal->atributo.nombre = lista->informacionLexema.informacion;
	
	fprintf(pArchivoAnaSin, "ARGUMENTOS -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	if( lista != NULL )
	{
		/* Aquí se considera que el caso en que una función es llamada
			sin parametros */
		if( lista->informacionLexema.lexema == PAREN_DER )
		temporal->hijo[0] == NULL;
		/* En que caso contrario ( que si tiene argumentos), entonces se llama
			a lista_argumentos() para hacer el respectivo tratamiento de parámetros
			actuales */
		else
		temporal->hijo[0] = lista_argumentos();
	}
	
	return temporal;
}

static NodoArbol *lista_argumentos( void )
{
	NodoArbol *temporal = expresion();
	NodoArbol *p = temporal;
	
	char identificador;
	fprintf(pArchivoAnaSin, "LISTA-ARGUMENTOS -->\n");
	fprintf(pArchivoAnaSin, "lexema: %d linea numero: %d valor cadena: %s\n",
	lista->informacionLexema.lexema, lista->informacionLexema.lineanumero,
	lista->informacionLexema.informacion);
	
	/* Hacer avanzar token y concordar con punto y coma si es posible. */
	if(lista->informacionLexema.lexema == OPERADOR_COMA)
	parearCompleto(OPERADOR_COMA);
	
	while( lista->informacionLexema.lexema != PAREN_DER)
	{
		NodoArbol *q;
		
		q = expresion();
		/* Hacer avanzar token y concordar con punto y coma si es posible. */
		if(lista->informacionLexema.lexema == OPERADOR_COMA)
		parearCompleto(OPERADOR_COMA);
		
		if( q != NULL )
		{
			if( temporal == NULL)
			temporal = p = q;
			else /* en este instante p no puede ser null */
			{
				p->hijoextra = q;
				p = q;
			}
		}
	} /* fin del while */
	
	return temporal;
}

/* funcion principal del analizador sintactico */
/* la funcion analizarSintaxis devuelve el arbol recien construido */

NodoArbol *analizarSintaxis( NodoListaLexema *listaLex )
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

} /* fin de la funcion analizarSintaxis */

/* nota: no olvidar colocar los datos al árbol que servirá para
	el analizador semántico y el generador de código */
