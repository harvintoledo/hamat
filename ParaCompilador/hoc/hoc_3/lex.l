%{
#include "hoc.h"
#include "y.tab.h"
extern int lineno;
%}
%%
[ \t] { ; } /* skip blanks and tabs */
/* Numero o flotante */
[0-9]+\.?|[0-9]*\.[0-9]+{
	sscanf(yytext, "%lf", &yylval.val);
	return NUMBER;
}
/* El identificador comienza con cualquier letra y sigue por una letra o digitos una o más veces */
/* Indentifier stars with a letter and the next symbol can be a letter or a digit */
[a-zA-Z][a-zA-Z0-9]* {
	Symbol *s;
	if((s = lookup(yytext)) == 0)
		s = install(yytext, UNDEF, 0.0);
	yylval.sym = s;
	return s->type == UNDEF ? VAR : s->type;
}
\n { lineno++; return '\n'; } /* Para todo lo demás */ /* Everything else */
. { return yytext[0]; }