/* Archivo instrucciones.y */
%{
#include <stdio.h>
#include <stdlib.h> /* para funcion realloc */
#include <math.h> /* para funciones sin, cos, tan y atan */
#include <ctype.h> /* para funciones isalnum y isalpha */
#include <string.h> /* para funcionestes strcmp y strcpy */
#include "util.h" /* Archivo con variables globales y utiles para el compilador */
%}

%union {
    double val;  /* Para devolver números                            */
    symrec  *tptr;   /* Para devolver punteros a la tabla de símbolos    */
}

%token  APAR CPAR NL
%token <val> CONSTFLOTANTE
%token <val> CONSTENTERA
%token <val> IDENTIFICADOR
%type <val> expresion
%right OPAS
%left MENOS MAS
%left POR ENTRE
%left MENORQUE MENOROIGUALQUE MAYORQUE MAYOROIGUALQUE IGUAL
%left NEG /* Negation -- unary minus */
%right POTENCIA /* Exponenciation */
%%
input:   /* empty */
        | input line
;
line: NL
    | expresion NL { printf("\t%.10g\n", $1);}
    | error NL { yyerrok; }
;
expresion :
    CONSTENTERA { $$ = $1; }
    | CONSTFLOTANTE { $$ = $1; }
    | IDENTIFICADOR {  $$ = $1; }
    /*| IDENTIFICADOR OPAS expresion {}*/
    /*| IDENTIFICADOR APAR expresion CPAR {}*/
    | expresion MAS expresion { $$ = $1 + $3; }
    | expresion MENOS expresion { $$ = $1 - $3; }
    | expresion POR expresion { $$ = $1 * $3; }
    | expresion ENTRE expresion { $$ = $1 / $3; }
    | MENOS expresion %prec NEG    { $$ = -$2; }
    | expresion POTENCIA expresion {$$ = pow($1, $3); }
    | APAR expresion CPAR { $$ = $2; }
;
%%
main() {
    printf("Teoria de compiladores.\n");
    printf("Invocando a funcion parse.\n");
    yyparse();
}

yyerror(s) /* Called by yyparse on error */
char *s;
{
    printf("%s\n", s);
}

