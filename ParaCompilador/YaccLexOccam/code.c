#include "hoc.h"
#include "y.tab.h"
#define NSTACK 256
static Datum stack[NSTACK];    /* the stack */
static Datum *stackp;        /* next free spot on stack */
#define NPROG 2000
Inst prog[NPROG]; /* the machine */
Inst *progp; /* next free spot for code generation */
Inst *pc; /* program counter during program execution */
Inst *progbase = prog; /* start of current subprogram */
int returning; /* 1 if return statement seen */
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
	progp = progbase;
	stackp = stack;
	fp = frame;
	returning = 0;
}
/* The stack is manipulated by calls to push and pop */
push(d) /* Push d data onto stack */
Datum d;
{
	if(stackp >= &stack[NSTACK])
	execerror("stack overflow", (char *)0);
	*stackp++ = d;
}
Datum pop() /* pop and return top element from stack */
{
	if(stackp <= stack)
	execerror("stack underflow", (char *)0);
	return *--stackp;
}
Inst *code(f) /* Install one instruction or operand */
Inst f;
{
	Inst *oprogp = progp;
	if(progp >= &prog[NPROG])
	execerror("program too big", (char *)0);
	*progp++ = f;
	return oprogp;
}
/* Execution of the machine is simple: in fact, it's rather neat how small the routine is that "runs" the machine it's set up:*/
execute(p) /* run de the machine */
Inst *p;
{
	for(pc = p; *pc != STOP && !returning;)
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
add()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val += d2.val;
	push(d1);
}
sub()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val -= d2.val;
	push(d1);
}
mul()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val *= d2.val;
	push(d1);
}
division()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val /= d2.val;
	push(d1);
}
power()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val = Pow(d1.val, d2.val);
	push(d1);
}
negate()
{
	Datum d;
	d = pop();
	d.val = -d.val;
	push(d);
}
eval() /* evaluate variable on stack */
{
	Datum d;
	d = pop();
	if(d.sym->type == UNDEF)
	execerror("undefined variable", d.sym->name);
	d.val = d.sym->u.val;
	push(d);
}
assign() /* assign top value to next value */
{
	Datum d1, d2;
	d1 = pop();
	d2 = pop();
	if(d1.sym->type != VAR && d1.sym->type != UNDEF)
	execerror("assigment to non variable", d1.sym->name);
	d1.sym->u.val = d2.val;
	d1.sym->type = VAR;
	push(d2);
}
print() /* pop top value from stack, print it */
{
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
		execute(*((Inst **)(savepc))); /* body */
		if(returning)
		break;
		execute(savepc+2); /* condition */
		d = pop();
	}
	if(!returning)
	pc = *((Inst **)(savepc+1)); /* next statement */
}
ifcode()
{
	Datum d;
	Inst *savepc = pc; /* then part */
	execute(savepc+3); /* condition */
	d = pop();
	if(d.val)
	execute(*((Inst **)(savepc)));
	else if(*((Inst **)(savepc+1))) /* Else part? */
	execute(*((Inst **)(savepc+1)));
	if(!returning)
	pc = *((Inst **)(savepc+2)); /* next stmt */
}
prexpr() /* print numeric value */
{
	Datum d;
	d = pop();
	printf("%.8g ", d.val);
}
define(sp) /* put func/proc in symbol table */
Symbol *sp;
{
	sp->u.defn = (Inst)progbase; /* start of code */
	progbase = progp; /* next code starts here */
}
call() /* call a function */
{
	Symbol *sp = (Symbol *)pc[0]; /* symbol table entry */
	/* for functions */
	if(fp++ >= &frame[NFRAME-1])
		execerror(sp->name, "call nested too deeply");
	fp->sp = sp;
	fp->nargs = (int)pc[1];
	fp->retpc = pc + 2;
	fp->argn = stackp - 1; /* last argument */
	execute(sp->u.defn);
	returning = 0;
}
funcret() /* return from a function */
{
	Datum d;
	if(fp->sp->type == PROCEDURE)
	execerror(fp->sp->name, "(proc) returns value");
	d = pop(); /* preserve function return value */
	ret();
	push(d);
}
/* The function ret() pops the arguments off the stack, restores the frame pointer fp, and sets the program counter. */
ret() /* common return from func or proc */
{
	int i;
	for(i = 0; i < fp->nargs; i++)
	pop(); /* pop arguments */
	pc = (Inst *)fp->retpc;
	--fp;
	returning = 1;
}
double *getarg() /* return pointer to argument */
{
	int nargs = (int) *pc++;
	if(nargs > fp->nargs)
	execerror(fp->sp->name, "not enough arguments");
	return &fp->argn[nargs-fp->nargs].val;
}
arg() /* push argument onto stack */
{
	Datum d;
	d.val = *getarg();
	push(d);
}
argassign() /* store top of stack in argument */
{
	Datum d;
	d = pop();
	push(d); /* leave value on stack */
	*getarg() = d.val;
}
prstr() /* print string value */
{
	printf("%s", (char *) *pc++);
}

varread() /* read into variable */
{
	Datum d;
	extern FILE *fin;
	Symbol *var = (Symbol *) *pc++;
Again:
	switch(fscanf(fin, "%lf", &var->u.val)) {
	case EOF:
		if(moreinput())
		goto Again;
		d.val = var->u.val = 0.0;
		break;
	case 0:
		execerror("non-number read into", var->name);
		break;
	default:
		d.val = 1.0;
		break;
	}
	var->type = VAR; /* set a type of variable */
	push(d); /* push into stack value of var */
}

procret()     /* return from a procedure */
{
	if (fp->sp->type == FUNCTION)
	execerror(fp->sp->name,
	"(func) returns no value");
	ret();
}
