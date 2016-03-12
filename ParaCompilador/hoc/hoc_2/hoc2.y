%{
#include <stdio.h>
double mem[26];
%}
%union {        /* stack type */
	double val; /* actual value */
	int index; /* index into mem */
}
%token <val> NUMBER
%token <index> VAR
%type <val> expr
%right '='
%left '+' '-'
%left '*' '/'
%left UNARYMINUS
%%
list: /* nothing */
	| list '\n'
	| list expr '\n' { printf("\t%.8g\n", $2); }
	| list error '\n' { yyerrok; }
	;
expr: NUMBER
	| VAR { $$ = mem[$1]; }
	| VAR '=' expr { $$ = mem[$1] = $3; }
	| expr '+' expr { $$ = $1 + $3; }
	| expr '-' expr { $$ = $1 - $3; }
	| expr '*' expr { $$ = $1 * $3; }
	| expr '/' expr { 
	if($3 == 0.0 )
		execerror("division by zero", "");
		$$ = $1 / $3;
	}
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
	if(islower(c)) {
		yylval.index = c -'a'; /* ASCII only */
		return VAR; /* return VAR token */
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

