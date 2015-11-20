struct symrec
{
  char *name;  /* nombre del símbolo                 */
  int type;    /* tipo del símbolo: bien VAR o FNCT  */
  union {
    double var;           /* valor de una VAR        */
    double (*fnctptr)();  /* valor de una FNCT       */
  } value;
  struct symrec *next;    /* campo de enlace         */
};

typedef struct symrec symrec;

/* La tabla de símbolos: una cadena de `struct symrec'.     */
extern symrec *sym_table;

symrec *putsym ();
symrec *getsym ();