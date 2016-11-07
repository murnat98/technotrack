#include "include.h"

int cpu_ctor(cpu_t * This)
{
	int ret = Stack_ctor(&This->stk, STACK_SIZE);
	assert(!ret);

	This->ax = This->bx = This->cx = This->dx = 0;
	This->pc = PROGSTART;

	return ret;
}

int cpu_dtor(cpu_t * This)
{
	int ret = Stack_dtor(&This->stk);
	assert(!ret);

	This->ax = This->bx = This->cx = This->dx = REGPOISON;
	This->pc = PCPOISON;

	return ret;
}

bool cpu_OK(cpu_t * This)
{
	assert(This);

	return Stack_OK(&This->stk);
}

int cpu_dump(const cpu_t * This, const char * VarName)
{
	assert(This);

	Stack_dump(&This->stk, VarName);

	FILE * dumpfile = fopen(DUMPFILENAM, "a+");
	fprintf(dumpfile, "Registers of CPU:\n\tax = %d\n\tbx = %d\n\tcx = %d\n\tdx = %d\nProgram counter: %ld\n", This->ax, This->bx, This->cx, This->dx, This->pc);
	fclose(dumpfile);

	return 0;
}

int cpu_pushc(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(1, cpu_pushc);
	assert(args);

	Stack_push(&This->stk, *args);

	ASSERTCPU(This);

	return size;
}

int cpu_pushr(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(1, cpu_pushr);
	assert(args);

	switch (*args)
	{
	#define DEFREG( reg, regnum )							\
	case regnum:											\
		Stack_push ( &This -> stk, This -> reg );			\
		break;

	#include "regs.h"

	#undef DEFREG
	}

	ASSERTCPU(This);

	return size;
}

int cpu_pop(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_pop);

	int ret = Stack_pop(&This->stk);

	ASSERTCPU(This);

	return size;
}

int cpu_popr(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(1, cpu_popr);
	assert(args);

	int ret = Stack_pop(&This->stk);
	switch (*args)
	{
	#define DEFREG( reg, num )			 \
	case num:							 \
		This -> reg = ret;				 \
		break;
		
	#include "regs.h"

	#undef DEFREG

	default:
		PRINTF("Cannot define register!\n");
	}

	ASSERTCPU(This);

	return size;
}

int cpu_add(cpu_t * This, const int * args, int size)
{ 
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_add);

	int sum1 = Stack_pop(&This->stk);
	int sum2 = Stack_pop(&This->stk);
	int sum = sum1 + sum2;

	Stack_push(&This->stk, sum);

	ASSERTCPU(This);

	return size;
}

int cpu_sub(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_add);

	int sub1 = Stack_pop(&This->stk);
	int sub2 = Stack_pop(&This->stk);
	int sub = sub2 - sub1;

	cpu_pushc(This, &sub, 1);
	Stack_push(&This->stk, sub);

	ASSERTCPU(This);

	return size;
}

int cpu_mul(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_add);

	int mul1 = Stack_pop(&This->stk);
	int mul2 = Stack_pop(&This->stk);
	int mul = mul1 * mul2;

	Stack_push(&This->stk, mul);

	ASSERTCPU(This);

	return size;
}

int cpu_div(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_add);

	int div1 = Stack_pop(&This->stk);
	int div2 = Stack_pop(&This->stk);
	int div = div1 / div2;

	Stack_push(&This->stk, div);

	ASSERTCPU(This);

	return size;
}

int cpu_jmp(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(1, cpu_jmpf);
	assert(args);

	This->pc = *args;

	ASSERTCPU(This);

	return -1;
}

int cpu_jmpf(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(1, cpu_jmpf);
	assert(args);

	int LastElem = Stack_get(&This->stk);
	if (!LastElem)
	{
		This->pc = *args;
		ASSERTCPU(This);

		return -1;
	}
	else
	{
		ASSERTCPU(This);

		return size;
	}

	return 0;
}

int cpu_call(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(1, cpu_call);
	assert(args);

	Stack_push(&This->stk, This->pc);

	ASSERTCPU(This);

	return cpu_jmp(This, args, size);
}

int cpu_ret(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_ret);
	assert(args);

	This->pc = Stack_pop(&This->stk);

	ASSERTCPU(This);

	return -1;
}

int cpu_equal(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_equal);

	int get1 = Stack_pop(&This->stk);
	int get2 = Stack_pop(&This->stk);
	if (get1 == get2)
		Stack_push(&This->stk, 1);
	else
		Stack_push(&This->stk, 0);

	ASSERTCPU(This);

	return size;
}

int cpu_noteq(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_noteq);

	int get1 = Stack_pop(&This->stk);
	int get2 = Stack_pop(&This->stk);
	if (get1 != get2)
		Stack_push(&This->stk, 1);
	else
		Stack_push(&This->stk, 0);

	ASSERTCPU(This);

	return size;
}

int cpu_boreq(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_boreq);

	int get1 = Stack_pop(&This->stk);
	int get2 = Stack_pop(&This->stk);
	if (get2 <= get1)
		Stack_push(&This->stk, 1);
	else
		Stack_push(&This->stk, 0);

	ASSERTCPU(This);

	return size;
}

int cpu_aoreq(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_uoreq);

	int get1 = Stack_pop(&This->stk);
	int get2 = Stack_pop(&This->stk);
	if (get2 >= get1)
		Stack_push(&This->stk, 1);
	else
		Stack_push(&This->stk, 0);

	ASSERTCPU(This);

	return size;
}

int cpu_below(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_below);

	int get1 = Stack_pop(&This->stk);
	int get2 = Stack_pop(&This->stk);
	if (get2 < get1)
		Stack_push(&This->stk, 1);
	else
		Stack_push(&This->stk, 0);

	ASSERTCPU(This);

	return size;
}

int cpu_above(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_above);

	int get1 = Stack_pop(&This->stk);
	int get2 = Stack_pop(&This->stk);
	if (get2 > get1)
		Stack_push(&This->stk, 1);
	else
		Stack_push(&This->stk, 0);

	ASSERTCPU(This);

	return size;
}

int cpu_and(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_and);

	int get1 = Stack_pop(&This->stk);
	int get2 = Stack_pop(&This->stk);
	Stack_push(&This->stk, get1 & get2);

	ASSERTCPU(This);

	return size;
}

int cpu_or(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_or);

	int get1 = Stack_pop(&This->stk);
	int get2 = Stack_pop(&This->stk);
	Stack_push(&This->stk, get1 | get2);

	ASSERTCPU(This);

	return size;
}

int cpu_not(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_not);

	int get1 = Stack_pop(&This->stk);
	Stack_push(&This->stk, ~get1);

	ASSERTCPU(This);

	return size;
}

int cpu_in(cpu_t * This, const int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_in);

	int in;
	scanf("%d", &in);
	Stack_push(&This->stk, in);

	ASSERTCPU(This);

	return size;
}

int cpu_out(cpu_t * This, const int * args, int size)
{ 
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_out);

	type out = Stack_pop(&This->stk);
	printf("%d\n", out);

	ASSERTCPU(This);

	return size; 
}

int cpu_exit(cpu_t * This, const int * args, int size)
{ 
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_exit);

	return 0; 
}