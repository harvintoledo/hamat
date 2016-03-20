#include <stdio.h>
typedef struct Symbol { /* Symbol table entry */
    char *name;
    short type; /* VAR, BLTIN, UNDEF */
    union {
        double val; /* if VAR */
        double (*ptr)(); /* if BLTIN */
        int (*defn)(); /* FUNCTION, PROCEDURE */
        char *str;
    } u;
    struct Symbol *next;
} Symbol;

Symbol *install(), *lookup();

typedef union Datum {
    double val;
    Symbol *sym;
} Datum;

extern Datum pop();
typedef int (*Inst)(); /* Machine instruction */
#define STOP (Inst) 0 

extern Inst prog[], *progp, *code();
extern eval(), add(), sub(), mul(), division(), negate(), power();
extern assign(), bltin(), varpush(), constpush(), print();
extern prexpr();
extern gt(), lt(), eq(), ge(), le(), ne(), and(), or(), not();
extern ifcode(), whilecode();


