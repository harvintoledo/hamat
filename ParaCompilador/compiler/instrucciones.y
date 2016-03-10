/* Archivo instrucciones.y*/
%{
#include <stdio.h>
%}
%token IDENTIFICADOR OPAS CONSTENTERA NL MAS APAR CPAR
%start instrucciones
%%
instrucciones : instrucciones instruccion
	| instruccion
	;
instruccion : IDENTIFICADOR OPAS expresion NL
expresion : termino | expresion MAS termino
	;
termino : IDENTIFICADOR | CONSTENTERA | APAR expresion CPAR
	;
%%
yyerror (s)
char *s; {
	printf("%s\n", s);
}
main () {
    /* Acciones a ejecutar antes del análisis sintáctico */
	yyparse();
	/* Acciones a ejecutar después del análisis sintáctico */
}