/* codigo.c */
#include "globales.h"
#include "codigo.h"
/* Número de localidad para la emisión de la instrucción actual */
static int emitLoc = 0;

/* Localidad más alta emitida hasta ahora
    Para su uso en conjunto con emitSkip,
    emitBackup y emitRestore */
static int highEmitLoc = 0;

/* 
    El procedimiento emitComment imprime una línea de comentario
    con un comentario c en el archivo de código
    */
void emitComment( char * c)
{
    if(TraceCode)
        fprintf(codigo, "* %s\n", c);
}

/*
    El procedimiento emitRO emite una
    instrucción solo de registro
    op = el opcode
    r = registro objetivo
    s = 1.er registro fuente
    t = 2.do registro fuente
    c = un comentario que para ser impreso si TraceCode es true
*/
void emitRO( char *op, int r, int s, int t, char *c )
{
    fprintf(codigo, "%3d: %5s %d, %d, %d", emitLoc++, op, r, s, t);
    
    if(TraceCode)
        fprintf(codigo, "\t%s", c);
    fprintf(codigo, "\n");
    
    if(highEmitLoc < emitLoc)
        highEmitLoc = emitLoc;
} /* fin de emitRO */

/*
    El procedimiento emitRM emite una instruccion 
    de registro-a-memoria
    op = codigo de operacion
    r = registro objetivo
    d = el desplazamiento
    s = el registro base
    c = un comentrio si TraceCode es TRUE
    */
    
void emitRM( char *op, int r, int d, int s, char *c)
{
    fprintf(codigo, "%3d:  %5s  %d, %d(%d) ", emitLoc++, op, r, d, s);
    
    if(TraceCode)
        fprintf(codigo, "\t%s", c);
    fprintf(codigo, "\n");
    
    if( highEmitLoc < emitLoc)
        highEmitLoc = emitLoc;
        
} /* emitRM */

/*
    La función emitSkip salta las localidades de código "howMany"
    para reajuste posterior. También
    devuelve la posición del código actual 
*/

int emitSkip( int howMany)
{
    int i=emitLoc;
    
    emitLoc+= howMany;
    
    if( highEmitLoc < emitLoc)
        highEmitLoc = emitLoc;
    
    return i;
}

/* el procedimiento emitBackup respalda a
    loc = una localidad previamente saltada
    */
void emitBackup( int loc)
{
    if( loc > highEmitLoc)
        emitComment("BUG in emitBackup");
    
    emitLoc = loc;
    
}
/* 
    El procedimiento emitRestore restablece
    la posicion de codigo actual a la posición mas alta
    no emitida previamente
    */
void emitRestore(void)
{
    emitLoc = highEmitLoc;
}

/*
    El procedimiento emitRM_Abs convierte una referencia absoluta
    en una referencia relativa al pc cuando se emite una
    intrucción de registro-a-memoria
    op = el opcode (código operacional)
    r = registro objetivo
    a = la localidad absoluta en memoria
    c = un comentario para imprimirse si TraceCode es TRUE
*/

void emitRM_Abs( char *op, int r, int a, char *c)
{
    fprintf(codigo, "%3d:  %5s %d, %d(%d) ", emitLoc, op, r, a-(emitLoc+1), pc);
    
    ++emitLoc;
    if(TraceCode)
        fprintf(codigo, "\t%s", c);
    fprintf(codigo, "\n");
    
    if( highEmitLoc < emitLoc)
        highEmitLoc = emitLoc;
} /* fin de función emitRM_Abs */

