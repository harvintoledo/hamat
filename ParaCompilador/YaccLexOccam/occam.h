#include <stdio.h>
typedef struct Symbol {    /* symbol table entry */
    char *name;
    short type; /* VAR, BLTIN, UNDEF */
    union {
        double val; /* if VAR */
        double (*ptr)(); /* if BLTIN */
        int (*defn)(); /* FUNCTION, PROCEDURE */
        char *str; /* STRING */
    } u;
    struct Symbol *next; /* to link to another */
} Symbol;

Symbol *install(), *lookup();

typedef union Datum { /* interpreter stack type */
    double val;
    Symbol *sym;
} Datum;

extern Datum pop();

extern eval(), add(), sub(), mul(), division(), negate(), power();
typedef int (*Inst)(); /* Machine instruction */
#define STOP (Inst) 0

extern Inst *progp, *progbase, prog[], *code();
extern assign(), bltin(), varpush(), constpush(), print(), varread();
extern prexpr(), prstr();
extern gt(), lt(), eq(), ge(), le(), ne(), and(), or(), not();
extern ifcode(), whilecode(), call(), arg(), argassign();
extern funcret(), procret();