#include "hoc.h"
#include "y.tab.h"
#define NPROG 2000
Inst prog[NPROG]; /* the machine */
Inst *progp; /* next free spot for code generation */
Inst *pc; /* program counter during program execution */
Inst *progbase = prog;
int returning; /* 1 if retur statement seen */

typedef struct Frame { /* proc/func call stack frame */
    Symbol *sp; /* symbol table entry */
    Inst *retpc; /* where to resume after return */
    Datum *argn; /* n-th argument on stack */
    int nargs; /* number of arguments */
} Frame;
#define NFRAME 100
Frame frame[NFRAME];
Frame *fp; /* frame pointer */


initcode() /* initialize for code generation */
{
    progp = prog;
    stackp = stack;
    fp = frame;
    returning = 0;
}
/* The stack is manipulated by calls to push and pop */
push(d) /* Push d data onto stack */
Datum d;
{
    if(stackp >= &stack[NSTACK])
    execerror("stack overflow", (char *) 0);
    *stackp++ = d;
}
Datum pop() /* pop and return top element from stack */
{
    if(stackp <= stack)
    execerror("stack underflow", (char *) 0);
    return *--stackp;
}
Inst *code(f) /* Install one instruction or operand */
Inst f; 
{
    Inst *oprogp = progp;
    if(progp >= &prog[NPROG])
    execerror("program too big", (char *) 0);
    *progp++ = f;
    return oprogp;
}
/* Execution of the machine is simple: in fact, it's rather neat how small the routine is that "runs" the machine it's set up:*/
execute(p) /* run de the machine */
Inst *p;
{
    for( pc = p; *pc != STOP; )
    (*(*pc++))();
}
constpush() /* push constant onto stack */
{
    Datum d;
    d.val = ((Symbol *)*pc++)->u.val;
    push(d);
}
varpush() /* push variable onto stack */
{
    Datum d;
    d.sym = (Symbol *)(*pc++);
    push(d);
}
add() {
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val += d2.val;
    push(d1);
}
sub() {
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val -= d2.val;
    push(d1);
}
mul() {
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val *= d2.val;
    push(d1);
}
division() {
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val /= d2.val;
    push(d1);
}
power() {
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = Pow(d1.val, d2.val);
    push(d1);
}
negate() {
    Datum d;
    d = pop();
    d.val = -d.val;
    push(d);
}
eval() /* evaluate variable on stack */
{
    Datum d;
    d = pop();
    if( d.sym->type == UNDEF)
    execerror("undefined variable", d.sym->name);
    d.val = d.sym->u.val;
    push(d);
}
assign() { /* assign top value to next value */
    Datum d1, d2;
    d1 = pop();
    d2 = pop();
    if(d1.sym->type != VAR && d1.sym->type != UNDEF)
    execerror("assigment to non variable", d1.sym->name);
    d1.sym->u.val = d2.val;
    d1.sym->type = VAR;
    push(d2);
}
print() {
    Datum d;
    d = pop();
    printf("\t%.8g\n", d.val);
}
bltin()
{
    Datum d;
    d = pop();
    d.val = (*(double (*)())(*pc++))(d.val);
    push(d);
}
lt()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val < d1.val);
}
gt()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val > d1.val);
}
eq()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val == d1.val);
}
ge()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val >= d1.val);
}
le()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val <= d1.val);
}
ne()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val != d1.val);
}
and()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val && d1.val);
}
or() 
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val || d1.val);
}
not()
{
    Datum d;
    d = pop();
    d.val = (double)(!d.val);
    push(d);
}
whilecode()
{
    Datum d;
    Inst *savepc = pc; /* loop body */
    execute(savepc+2); /* condition */
    d = pop();
    while(d.val) {
        execute(*((Inst **)(savepc))); /* body*/
        execute(savepc+2);
        d = pop();
    }
    pc = *((Inst **)(savepc+1)); /* next statement */
}

ifcode()
{
    Datum d;
    Inst *savepc = pc; /* then part */
    execute(savepc+3);
    d = pop();
    if(d.val)
        execute(*((Inst **)(savepc)));
    else if(*((Inst **)(savepc+1))) /* Else part? */
        execute(*((Inst **)(savepc+1)));
    pc = *((Inst **)(savepc+2)); /* next stmt */
}

prexpr() {
    Datum d;
    d = pop();
    printf("%.8g\n", d.val);
}

define(sp) /* put func/proc in symbol table */
    Symbol *sp;
{
    sp->u.defn = (Inst) progbase; /* start of code */
    progbase = progp; /* next code starts here */
}

call()
{
	Symbol *sp = (Symbol *)pc[0]; /* symbol table entry */
									/* for functions */
	fp->sp = sp;
	fp->nargs = (int) pc[1];
	fp->retpc = pc + 2;
	fp->argn = stackp - 1; /* last argument */
	execute(sp->u.defn);
	returning = 0;
}

funcret() 
{
	Datum d;
	if(fp->sp->type == PROCEDURE)
		execerror(fp->sp->name, "(proc) returns value");
	d = pop(); /* preserve function return  value */
	ret();
	push(d);
}

/* The function ret() pops the arguments off the stack, restores the frame pointer fp, and sets the program counter. */
ret()
{
	int i;
	for(i = 0; i < fp->nargs; i++)
		pop(); /* pop arguments */
	
}

