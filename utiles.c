/* utiles.c */
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

#include "globales.h"
#include "utiles.h"
#include <stdio.h> // nota: para prueba
void ImprimeLexemaSinFormato(TipoLexema lex, const char *cadena)
{
  switch(lex)
  {
    case ALCONTRARIO:
    case ARREGLO:
    case DE:
    case CADENA:
    case CARACTER:
    case CASO:
    case CLASE:
    case COMIENZO:
    case ENTONCES:
    case ENTERO:
    case FIN:
    case FUNCION:
    case HACER:
    case HASTA:
    case INTERRUMPIR:
    case MIENTRAS:
    case PARA:
    case PROCEDIMIENTO:
    case PROGRAMA:
    case REAL:
    case REPETIR:
    case SI:
    case SINO:
    case VAR:
    case PRIVADO:
    case PUBLICO:
    case PROTEGIDO:
    case RETORNAR:
    case SELECCIONAR:
    
      fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", cadena);
      break;
      
    case ASIGNACION:
      fprintf(pArchivoDestino, "=");
      break;
      
    case IGUALQUE:
      fprintf(pArchivoDestino, "==");
      break;
      
    case DIFERENTE:
      fprintf(pArchivoDestino, "<>");
      break;
      
    case MAYORQUE:
      fprintf(pArchivoDestino, ">");
      break;
      
    case MENORQUE:
      fprintf(pArchivoDestino, "<");
      break;
      
    case MA_IQUE:
      fprintf(pArchivoDestino, ">=");
      break;
      
    case MEN_IQUE:
      fprintf(pArchivoDestino, "<=");
      break;
      
    case OR:
      fprintf(pArchivoDestino, "||");
      break;
      
    case AND:
      fprintf(pArchivoDestino, "&&");
      break;
      
    case MAS:
      fprintf(pArchivoDestino, "+");
      break;
      
    case MENOS:
      fprintf(pArchivoDestino, "-");
      break;
      
    case POR:
      fprintf(pArchivoDestino, "*");
      break;
      
    case ENTRE:
      fprintf(pArchivoDestino, "/");
      break;
      
    case PAREN_DER:
      fprintf(pArchivoDestino, ")");
      break;
      
    case PAREN_IZQ:
      fprintf(pArchivoDestino, "(");
      break;
      
    case PARENTESISCUADRADO_IZQ:
      fprintf(pArchivoDestino, "[");
      break;
      
    case PARENTESISCUADRADO_DER:
      fprintf(pArchivoDestino, "]");
      break;
      
    case LLAVE_DER:
      fprintf(pArchivoDestino, "}");
      break;
      
    case LLAVE_IZQ:
      fprintf(pArchivoDestino, "{");
      break;
      
    case OPERADOR_COMA:
      fprintf(pArchivoDestino, ",");
      break;
      
    case PUNTOYCOMA:
      fprintf(pArchivoDestino, ";");
      break;
      
    case PUNTOFINAL:
      fprintf(pArchivoDestino, ".");
      break;
      
    case DOSPUNTOS:
      fprintf(pArchivoDestino, ":");
      break;
      
    case COMILLASIMPLE:
      fprintf(pArchivoDestino, "\'");
      break;
      
    case DOBLECOMILLA:
      fprintf(pArchivoDestino, "\"");
      break;
    case FINDEARCHIVO:
      fprintf(pArchivoDestino, "EOF");
      break;
      
    case ID:
      fprintf(pArchivoDestino, "<span class=\"nohemi-identificador\">%s</span>", cadena);
      break;
      
    case IDNUM:
      fprintf(pArchivoDestino, "<span class=\"nohemi-numero\">%s</span>", cadena);
      break;
      
    case IDCADENA:
      fprintf(pArchivoDestino, "<span class=\"nohemi-cadena\">&quot;%s&quot;</span>", cadena);
      break;
      
    case ERROR:
      fprintf(pArchivoDestino, "ERROR: %s\n", cadena);
      break;
      
    default:
      fprintf(pArchivoDestino, "Lexema DESCONOCIDO: %s\n", cadena);
  
  } /* fin del switch */
  
} /* fin de la funcion imprimirLexemaSinFormato */

void imprimirLexema(TipoLexema lex, const char *cadena)
{
  switch(lex)
  {
    case ALCONTRARIO:
    case ARREGLO:
    case DE:
    case CADENA:
    case CARACTER:
    case CASO:
    case CLASE:
    case COMIENZO:
    case ENTONCES:
    case ENTERO:
    case FIN:
    case FUNCION:
    case HACER:
    case HASTA:
    case INTERRUMPIR:
    case MIENTRAS:
    case PARA:
    case PROCEDIMIENTO:
    case PROGRAMA:
    case REAL:
    case REPETIR:
    case SI:
    case SINO:
    case VAR:
    case PRIVADO:
    case PUBLICO:
    case PROTEGIDO:
    case RETORNAR:
    case SELECCIONAR:
    
      fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", cadena);
      break;
      
    case ASIGNACION:
      fprintf(pArchivoDestino, "=");
      break;
      
    case IGUALQUE:
      fprintf(pArchivoDestino, "==");
      break;
      
    case DIFERENTE:
      fprintf(pArchivoDestino, "&lt;&gt");
      break;
      
    case MAYORQUE:
      fprintf(pArchivoDestino, "&gt;");
      break;
      
    case MENORQUE:
      fprintf(pArchivoDestino, "&lt;");
      break;
      
    case MA_IQUE:
      fprintf(pArchivoDestino, "&gt;=");
      break;
      
    case MEN_IQUE:
      fprintf(pArchivoDestino, "&lt;=");
      break;
      
    case OR:
      fprintf(pArchivoDestino, "||");
      break;
      
    case AND:
      fprintf(pArchivoDestino, "&amp;&amp;"); /* imprime && en el html */
      break;
      
    case MAS:
      fprintf(pArchivoDestino, "+");
      break;
      
    case MENOS:
      fprintf(pArchivoDestino, "-");
      break;
      
    case POR:
      fprintf(pArchivoDestino, "*");
      break;
      
    case ENTRE:
      fprintf(pArchivoDestino, "/");
      break;
      
    case PAREN_DER:
      fprintf(pArchivoDestino, ")");
      break;
      
    case PAREN_IZQ:
      fprintf(pArchivoDestino, "(");
      break;
      
    case PARENTESISCUADRADO_IZQ:
      fprintf(pArchivoDestino, "[");
      break;
      
    case PARENTESISCUADRADO_DER:
      fprintf(pArchivoDestino, "]");
      break;
      
    case LLAVE_DER:
      fprintf(pArchivoDestino, "}");
      break;
      
    case LLAVE_IZQ:
      fprintf(pArchivoDestino, "{");
      break;
      
    case OPERADOR_COMA:
      fprintf(pArchivoDestino, ",");
      break;
      
    case PUNTOYCOMA:
      fprintf(pArchivoDestino, ";");
      break;
      
    case PUNTOFINAL:
      fprintf(pArchivoDestino, ".");
      break;
      
    case DOSPUNTOS:
      fprintf(pArchivoDestino, "&#58;");
      break;
      
    case COMILLASIMPLE:
      fprintf(pArchivoDestino, "\'");
      break;
      
    case DOBLECOMILLA:
      fprintf(pArchivoDestino, "&quot;");
      break;
    case FINDEARCHIVO:
      fprintf(pArchivoDestino, "EOF");
      break;
      
    case ID:
      fprintf(pArchivoDestino, "<span class=\"nohemi-identificador\">%s</span>", cadena);
      break;
      
    case IDNUM:
      fprintf(pArchivoDestino, "<span class=\"nohemi-numero\">%s</span>", cadena);
      break;
      
    case IDCADENA:
      fprintf(pArchivoDestino, "<span class=\"nohemi-cadena\">&quot;%s&quot;</span>", cadena);
      break;
      
    case ERROR:
      fprintf(pArchivoDestino, "ERROR: %s\n", cadena);
      break;
      
    default:
      fprintf(pArchivoDestino, "Lexema DESCONOCIDO: %s\n", cadena);
  
  } /* fin del switch */
  
} /* fin de la funcion imprimirLexema */

void imprimirLexemaParaLista(TipoLexema lex)
{
  switch(lex)
  {
    case LLAMAR:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "llamar");
        break;
        
    case ALCONTRARIO:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "alcontrario");
        break;
        
    case ARREGLO:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "arreglo");
        break;
        
    case DE:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "de");
        break;
        
    case CADENA:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "cadena");
        break;
        
    case CARACTER:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "caracter");
        break;
        
    case CASO:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "caso");
        break;
        
    case CLASE:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "clase");
        break;
        
    case COMIENZO:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "comienzo");
        break;
        
    case ENTONCES:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "entonces");
        break;
        
    case ENTERO:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "entero");
        break;
        
    case FIN:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "fin");
        break;
        
    case FUNCION:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "funcion");
        break;
        
    case HACER:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "hacer");
        break;
        
    case HASTA: 
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "hata");
        break;
        
    case INTERRUMPIR:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "interrumpir");
        break;
        
    case MIENTRAS:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "mientras");
        break;
        
    case PARA:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "para");
        break;
        
    case PROGRAMA:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "programa");
        break;
        
    case REAL:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "real");
        break;
        
    case REPETIR:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "repetir");
        break;
        
    case SI:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "si");
        break;
        
    case SINO:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "sino");
        break;
        
    case VAR:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "var");
        break;
        
    case PRIVADO:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "privado");
        break;
        
    case PUBLICO:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "publico");
        break;
        
    case PROTEGIDO:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "protegido");
        break;
        
    case RETORNAR:
        fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "retornar");
        break;
        
    case SELECCIONAR:
    
      fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", "seleccionar");
      break;
      
    case ASIGNACION:
      fprintf(pArchivoDestino, "=");
      break;
      
    case IGUALQUE:
      fprintf(pArchivoDestino, "==");
      break;
      
    case DIFERENTE:
      fprintf(pArchivoDestino, "&lt;&gt");
      break;
      
    case MAYORQUE:
      fprintf(pArchivoDestino, "&gt;");
      break;
      
    case MENORQUE:
      fprintf(pArchivoDestino, "&lt;");
      break;
      
    case MA_IQUE:
      fprintf(pArchivoDestino, "&gt;=");
      break;
      
    case MEN_IQUE:
      fprintf(pArchivoDestino, "&lt;=");
      break;
      
    case OR:
      fprintf(pArchivoDestino, "||");
      break;
      
    case AND:
      fprintf(pArchivoDestino, "&amp;&amp;"); /* imprime && en el html */
      break;
      
    case MAS:
      fprintf(pArchivoDestino, "+");
      break;
      
    case MENOS:
      fprintf(pArchivoDestino, "-");
      break;
      
    case POR:
      fprintf(pArchivoDestino, "*");
      break;
      
    case ENTRE:
      fprintf(pArchivoDestino, "/");
      break;
      
    case PAREN_DER:
      fprintf(pArchivoDestino, ")");
      break;
      
    case PAREN_IZQ:
      fprintf(pArchivoDestino, "(");
      break;
      
    case PARENTESISCUADRADO_IZQ:
      fprintf(pArchivoDestino, "[");
      break;
      
    case PARENTESISCUADRADO_DER:
      fprintf(pArchivoDestino, "]");
      break;
      
    case LLAVE_DER:
      fprintf(pArchivoDestino, "}");
      break;
      
    case LLAVE_IZQ:
      fprintf(pArchivoDestino, "{");
      break;
      
    case OPERADOR_COMA:
      fprintf(pArchivoDestino, ",");
      break;
      
    case PUNTOYCOMA:
      fprintf(pArchivoDestino, ";");
      break;
      
    case PUNTOFINAL:
      fprintf(pArchivoDestino, ".");
      break;
      
    case DOSPUNTOS:
      fprintf(pArchivoDestino, "&#58;");
      break;
      
    case COMILLASIMPLE:
      fprintf(pArchivoDestino, "\'");
      break;
      
    case DOBLECOMILLA:
      fprintf(pArchivoDestino, "&quot;");
      break;
    case FINDEARCHIVO:
      fprintf(pArchivoDestino, "EOF");
      break;
      
    case ID:
      fprintf(pArchivoDestino, "<span class=\"nohemi-identificador\">%s</span>", " identificador ");
      break;
      
    case IDNUM:
      fprintf(pArchivoDestino, "<span class=\"nohemi-numero\">%s</span>", " numerico ");
      break;
      
    case IDCADENA:
      fprintf(pArchivoDestino, "<span class=\"nohemi-cadena\">&quot;%s&quot;</span>", " \"texto\"");
      break;
      
    case ERROR:
      fprintf(pArchivoDestino, "ERROR: %s\n", " en error ");
      break;
      
    default:
      fprintf(pArchivoDestino, "Lexema DESCONOCIDO: %s\n", " lexema desconocido ");
  
  } /* fin del switch */
  
} /* fin de la funcion imprimirLexemaParaLista */

/* Reserva memoria con informacion de un lexema */
NodoListaLexema *nuevoNodoLexema( InformacionLexema lex )
{
  NodoListaLexema *temporal = (NodoListaLexema *) malloc( sizeof(NodoListaLexema) );

  temporal->informacionLexema = lex;
  
  return temporal;
}

NodoArbol *nuevoNodoSentencia( TipoArbolSentencia descendiente )
{
  NodoArbol *temporal = (NodoArbol *) malloc( sizeof(NodoArbol) );
  int i;

  if( temporal == NULL )
    fprintf( pArchivoDestino, "No hay memoria en el sistema: error en la linea %d\n", lineanumero);
  else
  {
    for( i = 0; i < MAXNUMHIJOS; i++)
      temporal->hijo[i] = NULL;

    temporal->hijoextra = NULL;

    temporal->nododescendiente = NodoDescendienteSentencia;
    temporal->descendiente.tipoArbolSentencia = descendiente;
    temporal->lineanumero = lineanumero;
    
  }

  return temporal;
  
} /* fin de la funcion nuevoNodoSentencia */

NodoArbol *nuevoNodoExpresion( TipoArbolExpresion descendiente )
{
  NodoArbol *temporal = (NodoArbol *) malloc( sizeof(NodoArbol) );
  int i;

  if( temporal == NULL )
    fprintf( pArchivoDestino, "No hay memoria en el sistema: error en la linea %d\n", lineanumero);
  else
  {
    for( i = 0; i < MAXNUMHIJOS; i++)
      temporal->hijo[i] = NULL;

    temporal->hijoextra = NULL;
    temporal->nododescendiente = NodoDescendienteExpresion;
    temporal->descendiente.tipoArbolExpresion = descendiente;
    temporal->lineanumero = lineanumero;
    temporal->type = Void;
  }
  
  return temporal;
} /* fin de la funcion nuevoNodoExpresion */

/* La funcion copiarCadena asigna y hace una nueva copia de una cadena existente */
char *copiarCadena( char *cadena)
{
  int n;
  char *temporal;

  if( cadena == NULL )
    return NULL;

  n = strlen(cadena) + 1;
  
  temporal = (char *)malloc(n);
  if( temporal == NULL )
    fprintf(pArchivoDestino,"Fuera de memoria, error en la linea %d\n", lineanumero );
  else
    strcpy(temporal, cadena);

  return temporal;

} /* fin de la funcion copiarCadena */

static int indentno = 0;

/* macros para incrementar y decrementar la sangria */
#define IDENTAR indentno+=2

#define DESIDENTAR indentno-=2

static void imprimirEspacios( void )
{
  int i;

  for( i=0; i < indentno; i++ )
    fprintf( pArchivoDestino, " " );
    
} /* fin de la funcion imprimirEspacios */

/* el procedimiento imprimeArbol imprime un arbol sintactico
   al archivo de salida utilizando las sangrias para utilizar los subarboles */
void imprimirArbol( NodoArbol *arbol )
{
    int i;
    IDENTAR;
    
    while( arbol != NULL )
    {
        imprimirEspacios();
    
        if( arbol->nododescendiente == NodoDescendienteSentencia )
        {
            switch( arbol->descendiente.tipoArbolSentencia )
            {
                case TIPOARBOL_SENTENCIA_PARAMETRO:
                    fprintf(pArchivoDestino, "Parametro: %s\n", arbol->nombre );
                    break;

                case TIPOARBOL_SENTENCIA_TIPO_VARIABLE:
                    fprintf(pArchivoDestino, "Tipo Variable: %s\n", arbol->nombre );
                    break;
  
                case TIPOARBOL_SENTENCIA_DECLARACION_LOCAL:
                    fprintf(pArchivoDestino, "Declaracion local\n" );
                    break;

                case TIPOARBOL_SENTENCIA_DECLARACION_GLOBAL:
                    fprintf(pArchivoDestino, "Declaracion Global\n" );
                    break;

                case TIPOARBOL_FACTOR:
                    fprintf(pArchivoDestino, "Factor\n" );
                    break;

                case TIPOARBOL_EXPRESION:
                    fprintf(pArchivoDestino, "Expresion\n" );
                    break;

                case TIPOARBOL_EXPRESION_SENTENCIA:
                    fprintf(pArchivoDestino, "Expresion Sentencia\n" );
                    break;

                case TIPOARBOL_SENTENCIA_RETORNAR:
                    fprintf(pArchivoDestino, "Retornar\n" );
                    break;

                case TIPOARBOL_SENTENCIA_COMPUESTA:
                    fprintf(pArchivoDestino, "Sentencia Compuesta\n" );
                    break;
 
                case TIPOARBOL_SENTENCIA_PARAMETROS:
                    fprintf(pArchivoDestino, "Parametros\n" );
                    break;

                case TIPOARBOL_SENTENCIA_VAR:
                    fprintf(pArchivoDestino, "Variable\n" );
                    break;

                case TIPOARBOL_SI_SENTENCIA:
                    fprintf(pArchivoDestino, "Si\n" );
                    break;

                case TIPOARBOL_SENTENCIA_SELECCIONAR:
                    fprintf(pArchivoDestino, "Seleccionar\n");
                    break;

                case TIPOARBOL_CASO_SENTENCIA:
                    fprintf(pArchivoDestino, "Caso\n");
                    break;
   
                case TIPOARBOL_SENTENCIA_REPETIR:
                    fprintf(pArchivoDestino, "Repetir\n" );
                    break;

                case TIPOARBOL_SENTENCIA_PARA:
                    fprintf(pArchivoDestino, "Para\n");
                    break;

                case TIPOARBOL_SENTENCIA_MIENTRAS:
                    fprintf(pArchivoDestino, "Mientras\n");
                    break;
   
                case TIPOARBOL_SENTENCIA_PROGRAMA:
                    fprintf(pArchivoDestino, "Programa: %s\n", arbol->atributo.nombre);
                    break;
  
                case TIPOARBOL_SENTENCIA_DECLARACION:
                    fprintf(pArchivoDestino, "declaracion\n");
                    break;
  
                case TIPOARBOL_SENTENCIA_FUNCION:
                    fprintf(pArchivoDestino, "funcion: %s\n", arbol->atributo.nombre);
                    break;
 
                case TIPOARBOL_SENTENCIA_PROCEDIMIENTO:
                    fprintf(pArchivoDestino, "procedimiento: %s\n", arbol->atributo.nombre);
                    break;
  
                case TIPOARBOL_SENTENCIA_EXPLOG:
                    fprintf(pArchivoDestino, "expresion logica\n");
                    break;

                case TIPOARBOL_SENTENCIA_CLASE:
                    fprintf(pArchivoDestino, "clase\n");
                    break;
  
                case TIPOARBOL_SENTENCIA_CARACTER:
                    fprintf(pArchivoDestino, "caracter\n");
                    break;
  
                case TIPOARBOL_SENTENCIA_ENTERO:
                    fprintf(pArchivoDestino, "entero\n");
                    break;
  
                case TIPOARBOL_SENTENCIA_REAL:
                    fprintf(pArchivoDestino, "real\n");
                    break;

                case TIPOARBOL_SENTENCIA_CADENA:
                    fprintf(pArchivoDestino, "cadena\n");
                    break;
                case TIPOARBOL_SENTENCIA_ALCONTRARIO:
                    fprintf(pArchivoDestino, "alcontrario\n");
                    break;
                default:
                    fprintf(pArchivoDestino, "Nodo o tipo de expresion desconocido\n" );
                    break;

            } /* fin del switch */

        } /* fin del if */
        else
        if( arbol->nododescendiente == NodoDescendienteExpresion )
        {
            switch( arbol->descendiente.tipoArbolExpresion )
            {
                case TIPOARBOL_OPERADOR:
                    fprintf( pArchivoDestino, "Operador: " );
                    imprimirLexema( arbol->atributo.tipoLexemaOperador, "\n" );
                    break;

                case TIPOARBOL_CONSTANTE:
                    fprintf(pArchivoDestino, "Constante: %d\n", arbol->atributo.val );
                    break;

                case TIPOARBOL_IDENTIFICADOR:
                    fprintf(pArchivoDestino, "Identificador: %s\n", arbol->atributo.nombre );
                    break;

                case TIPOARBOL_CADENA:
                    fprintf(pArchivoDestino, "Cadena: %s\n", arbol->atributo.nombre );
                    break;
  
                case TIPOARBOL_LLAMADA:
                    fprintf(pArchivoDestino, "Llamada: %s\n", arbol->atributo.nombre );
                    break;
  
                case TIPOARBOL_VARIABLE:
                    fprintf(pArchivoDestino, "Variable: %s\n", arbol->atributo.nombre );
                    break;
 
                case TIPOARBOL_ARGUMENTOS:
                    fprintf(pArchivoDestino, "Argumentos: %s\n", arbol->atributo.nombre );
                    break;
  
                case TIPOARBOL_PARAMETROS_ACTUALES:
                    fprintf(pArchivoDestino, "Parametros actuales: %s\n", arbol->atributo.nombre );
                    break;
 
                default:
                    fprintf(pArchivoDestino, "Nodo de expresion desconocido\n");
                    break;
            } /* fin del switch */

        }/* fin del segundo if */
        else
            fprintf(pArchivoDestino, "Tipo de nodo desconocido\n");

        /* llamada recursiva a imprimir arbol */
        for( i = 0; i < MAXNUMHIJOS; i++)
            imprimirArbol( arbol->hijo[i]);

        arbol = arbol->hijoextra;
 
    } /* fin del while */

    DESIDENTAR;

} /* fin de la funcion imprimirArbol */
