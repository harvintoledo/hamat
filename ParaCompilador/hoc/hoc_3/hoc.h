typedef struct Symbol { /* Symbol table entry */
    char *name;
    short type; /* VAR, BLTIN, UNDEF */
    union {
        double val; /* if VAR */
        double (*prt)(); /* if BLTIN */
    } u;
    struct Symbol *next;
} Symbol;

Symbol *install(), *lookup();
