typedef struct Symbol { /* Symbol table entry */
    char *name;
    short type; /* VAR, BLTIN, UNDEF */
    union {
        double val; /* if VAR */
        double (*ptr)(); /* if BLTIN */
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

extern Inst prog[];
extern eval(), add(), sub(), mul(), division(), negate(), power();
extern assign(), bltin(), varpush(), constpush(), print();

