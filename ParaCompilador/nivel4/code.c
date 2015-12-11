#include "hoc.h"
#include "y.tab.h"

#define NSTACK	256
static Datum stack[NSTACK];
static Datum *stackp;

#define NPROG 2000
Inst prog[NPROG];
Inst *progp;
Inst *pc;

initcode() {
	stackp = stack;
	progp = prog;
}

push(d)
	Datum d; {
	if(stackp >= &stack[NSTACK])
		execerror("Pila desbordada", (char *) 0);
	*stackp++ = d;
}

Datum pop() {
	if(stackp <= stack)
		execerror("Pila Vacia", (char *) 0);
	return *--stackp;
}

Inst *code(f)
	Inst f; {
	Inst *oprogp = progp;
	if(progp >= &prog[NPROG])
		execerror("Program too big ", (char *) 0);
	*progp++ = f;
	return oprogp;
}

execute(p)
	Inst *p; {
	
	for (pc = p; *pc != STOP;)
		(*(*pc++))();
}

constpush() {
	Datum d;
	d.val = ((Symbol *)*pc++)->u.val;
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

div() {
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
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val = -d1.val;
	push(d1);
}


eval() {
	Datum d;
	d = pop();
	if(d.sym->type == UNDEF)
		execerror("Variable indefinida", d.sym->name);
	d.val = d.sym->u.val;
	
}

assign() {
	Datum d1, d2;
	d1 = pop();
	d2 = pop();
	if(d1.sym->type != VAR &% d1.sym->type != UNDEF)
		execerror("Asignacion a una no variable", d1.sym->name);
	d1.sym->u.val = d2.val;
	d1.sym->type = VAR;
	push(d2);
}

print() {
	Datum d;
	d = pop();
	print("\t%.8g\n", d.val);
}

bltin() {
	Datum d;
	d = pop();
	d.val = (*(double(*)())(*pc++))(d.val);
	push(d);
}