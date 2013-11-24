/* gencod.c */
#include "globales.h"
#include "tabsimb.h"
#include "codigo.h"
#include "gencod.h"

/*
    tmpOffset es el desplazamiento de memoria para elementos temporales
    Se decrementa cada vez que un elemento temporal es
    almacenado, y se incrementa cuando se carga de nuevo
*/
static int tmpOffset = 0;

/* prototipo para generador de código recursivo interno */
static void cGen(NodoArbol *arbol);

static void genStmt(NodoArbol *arbol)
{
    NodoArbol *p1, *p2, *p3;
    int savedLoc1, savedLoc2, currentLoc;
    int loc;
    
    switch(arbol->descendiente.tipoArbolSentencia)
    {
        case TIPOARBOL_SI_SENTENCIA:
            p1 = arbol->hijo[0];
            p2 = arbol->hijo[1];
            p3 = arbol->hijo[2];
            /* generar codigo para expresion de prueba */
            cGen(p1);
            savedLoc1 = emitSkip(1);
            emitComment("si: saltar a else aqui");
            /* recursividad para la parte then */
            cGen(p2);
            savedLoc2 = emitSkip(1);
            emitComment("si: salta hasta el final");
            currentLoc = emitSkip(0);
            emitBackup(savedLoc1);
            emitRM_Abs("JEG", ac, currentLoc, "si: jmp a sino");
            emitRestore();
            /* recursividad para la parte else*/
            cGen(p3);
            currentLoc = emitSkip(0);
            emitBackup(savedLoc2);
            emitRM_Abs("LDA", pc, currentLoc, "jmp al final");
            emitRestore();
            if(TraceCode)
                emitComment("<- if");
            break;
        case TIPOARBOL_SENTENCIA_REPETIR:
            if(TraceCode)
                emitComment("-> Repetir");
            p1 = arbol->hijo[0];
            p2 = arbol->hijo[1];
            savedLoc1 = emitSkip(0);
            emitComment("repetir: cuerpod e salto esta aqui");
            /* genera codigo para el cuerpo */
            cGen(p1);
            /* Genera codigo para prueba */
            cGen(p2);
            emitRM_Abs("JEG", ac, savedLoc1, "repetir: regresar al cuerpo");
            if(TraceCode)
                emitComment("<- repetir");
            break;
         /*   
        case TIPOARBOL_SENTENCIA_ASIGNAR:
            if(TraceCode)
                emitComment("<- asignar");
            cGen(arbol->hijo[0]);
            /* Ahora almacena valor */
            /*loc = st_lookup(arbol->atributo.nombre);
            emitRM("ST", ac, loc, gp, "Asignar: valor almacenado");
            if(TraceCode)
                emitComment("<- asignar");
            break;*/
            
        /*case TIPOARBOL_SENTENCIA_LEER:
            emitRO("IN", ac, 0, 0, "leer valor entero");
            loc = st_lookup(arbol->atributo.nombre);
            emitRM("ST", ac, 0, 0, "leer: almacenar valor");
            if(TraceCode)
                emitComment("<-Asignar");
            break;*/
         /*   
        case TIPOARBOL_SENTENCIA_ESCRIBIR:*/
            /* generar código para la expresión escribir */
           /* cGen(arbol->hijo[0]);*/
            /* Ahora los extras */
           /* emitRO("OUT", ac, 0, 0, "escribir ac");
            break;*/
        
        default:
            break;   
    }
}

/* El procedimiento genExp genera código en un nodo de expresión */
static void genExp(NodoArbol *arbol)
{
    int loc;
    NodoArbol *p1, *p2;
    
    switch(arbol->descendiente.tipoArbolExpresion)
    {
        case TIPOARBOL_CONSTANTE:
            if(TraceCode)
                emitComment("-> Constante");
            /* generar codigo cargar la constante utilizando LDC */
            emitRM("LDC", ac, arbol->atributo.val, 0, "carga constante");
            if(TraceCode)
                emitComment("<- Constante");
            break;
            
        case TIPOARBOL_IDENTIFICADOR:
            if(TraceCode)
                emitComment("-> Identificador");
            loc = st_lookup(arbol->atributo.nombre);
            emitRM("LD", ac, loc, gp, "cargar identificador valor");
            if(TraceCode)
                emitComment("<- Identificador");
            
            break;
            
        case TIPOARBOL_OPERADOR:
            if(TraceCode)
                emitComment("-> Identificador");
            p1 = arbol->hijo[0];
            p2 = arbol->hijo[1];
            /* genera código para ac = argumento izquierdo */
            cGen(p1),
            /* genera código para insertar operando izquierdo */
            emitRM("ST", ac, tmpOffset--, mp, "op: push left");
            /* genera código para ac = operando dercho */
            cGen(p2);
            /* ahora carga el operando izquierdo */
            emitRM("LD", ac1, ++tmpOffset, mp, "op: load left");
            
            switch(arbol->atributo.tipoLexemaOperador)
            {
                case MAS:
                    emitRO("ADD", ac, ac1, ac, "op +");
                    break;
                    
                case MENOS:
                    emitRO("SUB", ac, ac1, ac, "op -");
                    break;
                    
                case POR:
                    emitRO("MUL", ac, ac1, ac, "op *");
                    break;
                    
                case ENTRE:
                    emitRO("DIV", ac, ac1, ac, "op /");
                    break;
                    
                case MENORQUE:
                    emitRO("SUB", ac, ac1, ac, "op <");
                    emitRM("JLT", ac, 2, pc, "br if true");
                    emitRM("LDC", ac, 0, ac, "caso falso");
                    emitRM("LDA", pc, 1, pc, "salto incodicional");
                    emitRM("LDC", ac, 1, ac, "caso verdadero");
                    break;
                    
                case IGUALQUE:
                    emitRO("SUB", ac, ac1, ac, "op == ");
                    emitRM("JEQ", ac, 2, pc, "br if true");
                    emitRM("LDC", ac, 0, ac, "caso falso");
                    emitRM("LDA", pc, 1, pc, "salto incodicional");
                    emitRM("LDC", ac, 1, ac, "caso verdadero");
                    break;
                default:
                    emitComment("BUG:operador desconocido");
            } // fin de switch con case = tipoLexemaOperador
            if(TraceCode)
                emitComment("<- Op");
            break;
        default:
            break;
    } /* fin de switch con case = tipoArbolExpresion */
}

/*
    El procedimiento cGen genera código recursivamente mediante
    el recorrido del árbol
*/
static void cGen(NodoArbol *arbol)
{
    
    if(arbol != NULL)
    {
        switch(arbol->nododescendiente)
        {
            case NodoDescendienteSentencia:
                genStmt(arbol);
                break;
            case NodoDescendienteExpresion:
                genExp(arbol);
                break;
        }
    }
}

void generarCodigo(NodoArbol *arbolSintactico, char *archivocodigo)
{
    char *s = (char *)malloc(strlen(archivocodigo)+10);
    strcpy(s, "Archivo: ");
    strcat(s, archivocodigo);
    emitComment("Compilacion de Maquina hipotetica para Nohemi");
    emitComment(s);
    /* genera preludio estandar */
    emitComment("Preludio estandar");
    emitRM("LD", mp, 0, ac, "cargar maxaddress de la localizacion 0");
    emitRM("ST", ac, 0, ac, "borrar localización 0");
    emitComment("Fin del preludio estándar");
    /* genera codigo para el programa nohemi */
    cGen(arbolSintactico);
    /* final */
    emitComment("Fin de ejecucion");
    emitRO("HALT", 0, 0, 0, "");
}
