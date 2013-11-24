/* anasem.c */
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
#include "tabsimb.h"
#include "anasem.h"

static int location = 0;

/* contador para la localidades de memoria de variable */

/* El procedimiento traverse es uan rutina
    de recorrido del árbol sintáctico recursiva genérica:
    aplica preProc en preorden y postProc
    en postorden para el árbol al que apunta mediante t
*/
static void traverse(NodoArbol * t,
    void (*preProc) (NodoArbol *),
    void (*postProc) (NodoArbol *))
{
    if(t!=NULL)
    {
        preProc(t);
        {
            int i;
            for(i=0; i < MAXNUMHIJOS; i++)
                traverse(t->hijo[i], preProc, postProc);
        }
        postProc(t);
        traverse(t->hijoextra, preProc, postProc);
    }
}
      
      
/* nullProc ES UN PROCEDIMINETO QUE NO HACE NDA PARA
GENERAR RECORRIDOS SOLAMENTE PREORDEN O SOLAMENTE POSTOREEN A
PARTIR DE TRAVERSE
*/
static void nullProc(NodoArbol *t)
{
    if(t==NULL)
        return;
    else
        return;
}

/* 
    El procedimiento insertaNodo inserta
    identificadores almacenados en t dentro de la
    tabla de símbolos
*/

static void insertarNodo(NodoArbol *t)
{
    switch( t->nododescendiente)
    {
        case NodoDescendienteSentencia:
            switch(t->descendiente.tipoArbolSentencia)
            {
                /*
                case TIPOARBOL_SENTENCIA_LEER:
                        /* todavía no está en la tabla, de modo que se trata como nueva definición */
                        /*if(st_lookup(t->atributo.nombre) == -1)
                            st_insert(t->atributo.nombre, t->lineanumero, location++);
                        else
                        /* ya está en la tabla, así que se ignora la ubicación,
                         se agrega el número de línea de uso solamente*/
                         st_insert(t->atributo.nombre, t->lineanumero, 0);
                         break;
                default:
                        break;
            }
            break;
            
        case NodoDescendienteExpresion:
            
            switch(t->descendiente.tipoArbolExpresion)
            {
                case TIPOARBOL_IDENTIFICADOR:
                    /* todavia no esta en la tabla, de modo que se trata como nueva definición */
                    if(st_lookup( t->atributo.nombre ) == -1 )
                        st_insert(t->atributo.nombre, t->lineanumero, 0);
                    break;
                default:
                    break;
            } 
        break;
    }
} /* fin de la función insertaNodo */

/* la función construyeTablaSimbolos construye la tabla de simbolos
    mediante recorrido preorden del árbol sintáctico
    */
void construyeTablaSimbolos(NodoArbol *arbolSintactico)
{
    traverse(arbolSintactico, insertarNodo, nullProc);
    if(TraceAnalize)
    {
        fprintf(pArchivoDestino, "\nTabla de simbolos: \n\n");
        imprimirTablaDeSimbolos(pArchivoDestino);
    }
}
    
static void escribirError(NodoArbol *t, char *mensaje)
{
    /* escribe el mensaje en el archivo html */
    fprintf(pArchivoDestino, "Tipo de error en la linea %d: %s\n", t->lineanumero, mensaje);
    Error = VERDADERO;    
}    

/*  
    El procedimiento chequearNodo efectua
    verificación de tipo para un solo nodo de arbol 
*/
static void chequearNodo(NodoArbol *t)
{
    switch(t->nododescendiente)
    {
        case NodoDescendienteExpresion:
            switch(t->descendiente.tipoArbolExpresion)
            {
                case TIPOARBOL_OPERADOR:
                    if((t->hijo[0]->type != Entero) || (t->hijo[1]->type != Entero))
                        escribirError(t, "El operador aplicado no es un entero");
                    if((t->atributo.tipoLexemaOperador == IGUALQUE) || (t->atributo.tipoLexemaOperador == MENORQUE))
                        t->type = Booleano;
                    else
                        t->type = Entero;
                    break;
                case TIPOARBOL_CONSTANTE:
                case TIPOARBOL_IDENTIFICADOR:
                    t->type = Entero;
                    break;
                default:
                    break;
                        
            }
            break;
        case NodoDescendienteSentencia:
            switch(t->descendiente.tipoArbolSentencia)
            {
                case TIPOARBOL_SI_SENTENCIA:
                    if(t->hijo[0]->type == Entero)
                        escribirError(t->hijo[0], "La prueba para la sentancia \"Si\" no es Booleana");
                        break;
                        /*
                case TIPOARBOL_SENTENCIA_ASIGNAR:
                    if(t->hijo[0]->type != Entero)
                        escribirError(t->hijo[0], "Se esta intentando asignar un tipo diferente que no es entero");
                        break;
                case TIPOARBOL_SENTENCIA_ESCRIBIR:
                    if(t->hijo[0]->type != Entero)
                        escribirError(t->hijo[0], "El valor a escribir no es un entero");
                        break;*/
                case TIPOARBOL_SENTENCIA_REPETIR:
                    if(t->hijo[1]->type == Entero)
                        escribirError(t->hijo[1], "La prueba para la sentencia \"Repetir\" no es Booleana");
                        break;
                default:
                    break;   
            }
            break;
        default:
            break;
            
    } /* fin de switch principal*/
} /* fin de la función chequearNodo */


