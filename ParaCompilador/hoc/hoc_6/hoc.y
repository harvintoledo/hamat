%{
#include "hoc.h"
#include <stdio.h>
#define code2(c1, c2) code(c1); code(c2)
#define code3(c1, c2, c3) code(c1); code(c2); code(c3)
%}
%union { /* stack type */
    Symbol *sym; /* symbol table pointer */
    Inst *inst; /* Machine instruction */
    int narg; /* Number of argument for a function */
    int narg; /* Number of argument for a function */
}
%token <sym> NUMBER PRINT VAR BLTIN UNDEF WHILE IF ELSE /* This version provides if-else and while statements like those C */
%token <sym> FUNCTION PROCEDURE RETURN FUNC PROC READ
%token <narg> ARG
%type <inst> expr stmt asgn prlist stmtlist
%type <inst> cond while if begin end
%type procname
%type <narg> arglist
%right    '='
%left    OR
%left    AND
%left    GT GE LT LE EQ NE
%left    '+' '-'
%left    '*' '/'
%left    UNARYMINUS NOT
%right    '^' /* exponentiation */
%%
/* This grammar has five shift/reduce conflicts, It needs to solve these conflicts */
list: /* nothing */
| list '\n'
| list defn '\n'
| list asgn '\n' { code2(pop, STOP); return 1; }
| list stmt '\n' { code(STOP); return 1; }
| list expr '\n' { code2(print, STOP); return 1; }
| list error '\n' { yyerrok; }
;
asgn:    VAR '=' expr { code3(varpush, (Inst)$1, assign); $$ = $3; }
| ARG '=' expr { defonly("$"); code2(argassign, (Inst)$1); $$ = $3; }
;
stmt:    expr { code(pop); }
| RETURN { defonly("return"); code(procret); }
| RETURN expr { defonly("return"); $$ = $2; code(funcret); }
| PROCEDURE begin '(' arglist ')' { $$ = $2; code3(call, (Inst)$1, (Inst)$4); } 
| PRINT prlist { $$ = $2; }
| while cond stmt end {
    ($1)[1] = (Inst)$3; /* body of loop */
    ($1)[2] = (Inst)$4; } /* end, if cond fails */
| if cond stmt end { /* else-less if */
    ($1)[1] = (Inst)$3; /* then part */
    ($2)[3] = (Inst)$4; } /* end, if cond fails */
| if cond stmt end ELSE stmt end {
    ($1)[1] = (Inst)$3; /* thenpart */
    ($1)[2] = (Inst)$6; /* elsepart */
    ($1)[3] = (Inst)$7; }/* end, if cond fails */
| '{' stmtlist '}' { $$=$2; }
;
cond: '(' expr ')' { code(STOP); $$ = $2; }
;
while: WHILE { $$=code3(whilecode, STOP, STOP); }
;
if: IF { $$=code(ifcode); code3(STOP, STOP, STOP); }
;
end: /* nothing */ { code(STOP); $$=progp; }
;
stmtlist: /* nothing */ { $$=progp; }
| stmtlist '\n'
| stmtlist stmt
;
expr: NUMBER { $$ = code2(constpush, (Inst)$1); }
| VAR { $$ = code3(varpush, (Inst)$1, eval); }
| ARG { defonly("$"); $$ = code2(arg, (Inst)$1); }
| asgn
| FUNCTION begin '(' arglist ')' { $$ = $2; code3(call, (Inst)$1, (Inst)$4); }
| READ '(' VAR ')' { $$ = code2(varread, (Inst)$3); }
| BLTIN '(' expr ')' { $$ = $3; code2(bltin, (Inst)$1->u.ptr); }
| '(' expr ')' { $$=$2; }
| expr '+' expr { code(add); }
| expr '-' expr { code(sub); }
| expr '*' expr { code(mul); }
| expr '/' expr { code(division); }
| expr '^' expr { code(power); }
| '-' expr %prec UNARYMINUS { $$ = $2; code(negate); } // Action of this senteces is to change de sign of expression value
| expr GT expr { code(gt); }
| expr GE expr { code(ge); }
| expr LT expr { code(lt); }
| expr LE expr { code(le); }
| expr EQ expr { code(eq); }
| expr NE expr { code(ne); }
| expr AND expr { code(and); }
| expr OR expr { code(or); }
| NOT expr { $$=$2; code(not); }
;
begin: /* nothing */ { $$ O progp; }
;
prlist: expr { code(prexpr); }
| STRING { $$ = code2(prstr, (Inst)$1); }
| prlist ',' expr { code(prexpr); }
| prlist ',' STRING { code2(prstr, (Inst)$3); }
;
defn: FUNC procname { $2->type = FUNCTION; indef = 1; } '(' ')' stmt { code(procret); define($2); indef = 0; }
| PROC procname { $->type = PROCEDURE; indef = 1; }
    '(' ')' stmt { code(procret); define($2); indef = 0; }
;
procname: VAR
| FUNCTION
| PROCEDURE
;
arglist: /* nothing */ { $$ = 0; } /* The production por arglist count the arguments */
| expr { $$ = 1; } 
| arglist ',' expr { $$ = $1 + 1; }
;
%%
/* end of grammar */
#include <ctype.h>
char *progname; /* for error messages */
int lineno = 1;
#include <signal.h>
#include <setjmp.h>
jmp_buf begin;
main(argc, argv) /* hoc3 */
char *argv[]; {
    int fpecatch();  
    progname = argv[0];
    init();
    setjmp(begin);
    signal(SIGFPE, fpecatch);
    for( initcode(); yyparse(); initcode())
        execute(prog);
    yyparse();
}
defonly(s) 
    char *s; {
        if(!indef)
            execerror(s, "used outside definition");
}

yylex() /* hoc3 */
{
    int c;
    while ( (c = getchar()) == ' ' || c == '\t' )
    ;
    if (c == EOF)
    return 0;
    if (c == '.' || isdigit(c)) { /* number */
        double d;
        ungetc(c, stdin);
        scanf("%lf", &d);
        yylval.sym = install("", NUMBER, d);
        return NUMBER;
    }
    if (isalpha(c)) {
        Symbol *s;
        char sbuf[100], *p = sbuf;
        do {
            *p++ = c;
        }
        while ((c = getchar()) != EOF && isalnum(c));
        ungetc(c, stdin);
        *p = '\0';
        if ((s = lookup(sbuf)) == 0)
        s = install(sbuf, UNDEF, 0.0);
        yylval.sym = s;
        return s->type == UNDEF ? VAR : s->type;
    }
    if( c == '$') { /* argument ? */
        int n = 0;
        while(isdigit(c = getc(fin)))
            n = 10 * n + c- '0';
            ungetc(c, fin);
            if(n == 0)
                execerror("strange $...", (char *)0);
            yylval.narg = n;
            return ARG;
    }
    if( c == '"') { /* quoted string */
        char sbuf[], *p, *emalloc();
        for (p = sbuf; (c=getc(fin)) != '"'; p++) {
            if(c == '\n' || c == EOF)
                execerror("missing quote", "");
            if( p >= sbuf + sizeof(sbuf) -1) {
                *p = '\0';
                execerror("string too long", sbuf);
            }
            *p = backslash(c);
        }
        *p = 0;
        yylval.sym = (Symbol *)emalloc(strlen(sbuf)+1);
        strcpy(yylval.sym, sbuf);
        return STRING;
    }
    switch(c) {
        case '>': return follow('=', GE, GT);
        case '<': return follow('=', LE, LT);
        case '=': return follow('=', EQ, '=');
        case '!': return follow('=', NE, NOT);
        case '|': return follow('|', OR, '|');
        case '&': return follow('&', AND, '&');
        case '\n': lineno++; return '\n';
        default: return c;
    }
    return c;
}

backslash(c)
    int c;
{
    char *index(); /* 'strchr()' in some system */
    static char transtab[] = "b\bf\fn\nr\rt\t";
    if(c != '\\')
        return c;
    c = getc(fin);
    if(islower(c) && index(transtab, c))
        return index(transtab, c)[1];
    return c;
}
follow(expected, ifyes, ifno)
{ /* look ahead for >=, <=, etc. */
    int c = getchar();
    
    if(c == expected)
        return ifyes;
    ungetc(c, stdin);
    return ifno;
}
yyerror(s)
char *s;
{ 
    warning(s, (char *)0);
}
execerror(s, t) /* recover from run-time error */
char *s, *t;
{
    warning(s, t);
    longjmp(begin, 0);
}
fpecatch() /* catch floating point exceptions */
{
    execerror("floating point exception", (char *) 0);
}
warning(s, t)
char *s, *t;
{
    fprintf(stderr, "%s: %s", progname, s);
    if (t && *t)
    fprintf(stderr, " %s", t);
    fprintf(stderr, " near line %d\n", lineno);
}
