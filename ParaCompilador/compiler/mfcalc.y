/* Infix notation calculator --*/
/* ampliated with functions */
/* C declarations */
%{
#include <math.h> /* para funciones sin, cos, tan y atan */
#include <stdio.h>
#include <stdlib.h> /* para funcion realloc */
#include <ctype.h> /* para funciones isalnum y isalpha */
#include <string.h> /* para funcionestes strcmp y strcpy */
#include "calc.h"
%}
/* Bison declarations */
%union {
    double val;   /* For returning numbers. */
    symrec *tptr; /* For returning symbol-table pointers. */
}
%token <val> NUM /* Simple double precision number */
%token <tptr> VAR FNCT /* Variable and funcion */
%type <val> exp
%right '='
%left '-' '+'
%left '*' '/'
%left NEG /* Negation -- unary minus */
%right '^' /* Exponenciation */
/* Grammars follow */
%%
input: /* empty string */
    | input line
;
line: '\n'
    | exp '\n' { printf("\t%.10g\n", $1);}
    | error '\n' { yyerrok; }
;
exp: NUM                   { $$ = $1;                              }
    | VAR                  { $$ = $1->value.var;                   }
    | VAR '=' exp          { $$ = $3; $1->value.var = $3;          }
    | FNCT '(' exp ')'     { $$ = (*($1->value.fnctptr))($3);      }
    | exp '+' exp          { $$ = $1 + $3;                         }
    | exp '-' exp          { $$ = $1 - $3;                         }
    | exp '*' exp          { $$ = $1 * $3;                         }
    | exp '/' exp          { $$ = $1 / $3;                         }
    | '-' exp %prec NEG    { $$ = -$2;                             }
    | exp '^' exp          { $$ = pow($1, $3);                     }
    | '(' exp ')'          { $$ = $2;                              }
;
%%
/* Insert the symbol table */
/* C code */
/* Here we write c code */
init_table();
main() {
	printf("Teoria de compiladores.\n");
	printf("Invocando a funcion parse.\n");
	init_table();
	yyparse();
}
yyerror(s) /* Called by yyparse on error */
char *s;
{
	printf("%s\n", s);
}
struct init {
	char *fname; /* Function name */
	double (*fnct)(); /* Pointer to a function retunrs a double */
};
struct init arith_fncts [] = {
	"sin", sin,
	"cos", cos,
	"tan", tan,
	"atan", atan,
	"ln", log,
	"exp", exp,
	"sqrt", sqrt,
	0, 0
};
/* The symbol table: a chain of 'struct symrec' */
symrec *sym_table = (symrec *)0;
init_table() { /* puts arithmetic function in table */
	int i;
	symrec *ptr;
	for(i = 0; arith_fncts[i].fname != 0; i++) {
		ptr = putsym (arith_fncts[i].fname, FNCT);
		ptr->value.fnctptr = arith_fncts[i].fnct;
	}
}
symrec *putsym (sym_name, sym_type)
char *sym_name;
int sym_type; {
	symrec *ptr;
	ptr = (symrec *) malloc(sizeof(symrec));
	ptr->name = (char *) malloc(strlen(sym_name) + 1);
	strcpy(ptr->name, sym_name);
	ptr->type = sym_type;
	ptr->value.var = 0; /* set value to 0 even if fctn. */
	ptr->next = (struct symrec *)sym_table;
	sym_table = ptr;
	return ptr;
}
symrec *getsym(sym_name) 
char * sym_name; {
	symrec *ptr;
	for(ptr = sym_table; ptr != (symrec *)0; ptr = (symrec *)ptr->next)
	if(strcmp(ptr->name, sym_name) == 0)
	return ptr;
	return 0;
}
/* Lexical analyzer returns a double floating point
number on the stack and the token NUM, or the ASCII
character read it not a number. Skips all blanks
and tabs, returns 0 for EOF
*/
yylex() {
	int c;
	/* ignore whitespace, get first nonwhite character. */
	while(( c = getchar()) == ' ' || c == '\t');
	/* process number */
	
	/* return end of file */
	if( c == EOF)
	return 0;
	
	/* Char starts a number => parse a number */
	if( c == '.' || isdigit(c)) {
		ungetc(c, stdin);
		scanf("%lf", &yylval.val);
		return NUM;
	}
	
	/* Char starts an identifier => read the name */
	
	if( isalpha(c)) {
		symrec *s;
		static char *symbuf = 0;
		static int length = 0;
		int i;
		/* Initially  make the buffer long enough 
		for a 40-character symbol name. */
		if(length == 0)
		length = 40, symbuf = (char *)malloc(length + 1);
		
		i = 0;
		
		do {
			/* If buffer is full, make it bigger. */
			if( i == length) {
				length *= 2;
				symbuf = (char *)realloc(symbuf, length + 1);
			}
			/* Add this character to the buffer. */
			symbuf[i++] = c;
			/* Get another character. */
			c = getchar();
		}
		while( c != EOF && isalnum(c));
		
		ungetc(c, stdin);
		
		symbuf[i] = '\0';
		
		s = getsym (symbuf);
		
		if(s == 0)
		s = putsym(symbuf, VAR);
		
		yylval.tptr = s;
		return s->type;
		
	}
	/* Any other character is a toke by itself */
	
	return c;
}
