%{
#include "hoc.h"
#include <stdio.h>
extern double Pow();
%}
%union {        /* stack type */
	double val; /* actual value */
	Symbol *sym; /* symbol table pointer */
}
%token <val> NUMBER
%token <sym> VAR BLTIN UNDEF
%type <val> expr asgn
%right '='
%left '+' '-'
%left '*' '/'
%left UNARYMINUS
%right '^'
%%
list: /* nothing */
	| list '\n'
	| list asgn '\n'
	| list expr '\n' { printf("\t%.8g\n", $2); }
	| list error '\n' { yyerrok; }
	;
	asgn: VAR '=' expr {
		$$ = $1->u.val = $3;
		$1->type = VAR;
	}
	;
expr: NUMBER
	| VAR { if( $1->type == UNDEF)
				execerror("undefined variable", $1->name);
				$$ = $1->u.val;
	}
	| asgn
	| BLTIN '(' expr ')' { $$ = (*($1->u.ptr))($3); }
	| expr '+' expr { $$ = $1 + $3; }
	| expr '-' expr { $$ = $1 - $3; }
	| expr '*' expr { $$ = $1 * $3; }
	| expr '/' expr { 
	if($3 == 0.0 )
		execerror("division by zero", "");
		$$ = $1 / $3;
	}
	|  expr '^' expr { $$ = Pow($1, $3); }
	|  '(' expr ')' { $$ = $2; }
	| '-' expr %prec UNARYMINUS { $$ = -$2; } // Action of this senteces is to change de sign of expression value
	;
%%
/* end of grammar */

#include <ctype.h>
#include <signal.h>
#include <setjmp.h>
char *progname; /* for error messages */
int lineno = 1;
jmp_buf begin;

main( argc, argv)
char *argv[]; {
	int fpecatch();
	
	progname = argv[0];
	init();
	setjmp(begin);
	signal(SIGFPE, fpecatch);
	yyparse();
}

execerror(s, t)
	char *s, *t; {
	warning(s, t);
	longjmp(begin, 0);
}

fpecatch() {
	execerror("floating point exception", (char *) 0);
}
yylex() {
	int c;
	while( (c=getchar()) == ' ' || c == '\t' )
		;
	if( c == EOF)
		return 0;
	if( c == '.' || isdigit(c)) {
		ungetc(c, stdin);
		scanf("%lf", &yylval.val);
		return NUMBER; /* return NUMBER token */
	}
//	if(islower(c)) {
//		yylval.index = c -'a'; /* ASCII only */
//		return VAR; /* return VAR token */
//	}
	
	if(isalpha(c)) {
		Symbol *s;
		char *sbuf[100], *p = sbuf;
		do {
			*p++ = c;
		}
		while((c = getchar()) != EOF && isalnum(c));
		ungetc(c, stdin);
		*p = '\0';
		if((s = lookup(sbuf)) == 0)
			s = install(sbuf, UNDEF, 0.0);
		yylval.sym = s;
		return s->type == UNDEF ? VAR : s->type;
	}
	
	if(c == '\n' )
		lineno++;
	return c;
}

yyerror(s)
	char *s; {
	warning(s, (char *) 0);
}

warning(s, t)
		char *s, *t; {
		fprintf(stderr, "%s: %s", progname, s);

		if(t)
			fprintf(stderr, " %s", t);
		fprintf(stderr, " near line %d\n", lineno);
}

