/* Infix notation calculator --*/
/* C declarations */
%{
#define YYSTYPE double
#include <math.h>
#include <stdio.h>
%}

/* Bison declarations */
%token NUM
%left '-' '+'
%left '*' '/'
%left NEG /* negation -- unary minus */
%right '^'


/* Grammars follow */
%%
input: /* empty string */
     | input line
     ;
line: '\n'
    | exp '\n' { printf("\t%.10g\n", $1);}
;

exp: NUM    { $$ = $1;}
    | exp '+' exp {$$ = $1 + $3;}
    | exp '-' exp {$$ = $1 - $3;}
    | exp '*' exp {$$ = $1 * $3;}
    | exp '/' exp {$$ = $1 / $3;}
    | '-' exp %prec NEG { $$ = -$2;}
    | exp '^' exp {$$ = pow($1, $3);}
    | '(' exp ')' {$$ = $2;}
;
%%

/* C code */
/* Here we write c code */
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

/* Lexical analyzer returns a double floating point
number on the stack and the token NUM, or the ASCII
character read it not a number. Skips all blanks
and tabs, returns 0 for EOF
*/
#include <ctype.h>
yylex() {
    int c;
    /* skip white space */
    while(( c = getchar()) == ' ' || c == '\t');
    /* process number */
    if( c == '.' || isdigit(c)) {
     ungetc(c, stdin);
     scanf("%lf", &yylval);
     return NUM;
    }
    
    /* return end of file */
    if( c == EOF)
     return 0;
    /* return single char */
     
    return c;
}



