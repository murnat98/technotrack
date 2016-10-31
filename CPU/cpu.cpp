#include "main.h"

int cpu_ctor(cpu_t * This)
{
	assert(!Stack_ctor(&This->stk, STACK_SIZE));

	return 0;
}

int cpu_dtor(cpu_t * This)
{
	assert(!Stack_dtor(&This->stk));

	return 0;
}

bool cpu_OK(cpu_t * This)
{
	return Stack_OK(&This->stk);
}

int cpu_dump(const cpu_t * This, const char * VarName)
{
	Stack_dump(&This->stk, VarName);

	return 0;
}

int cpu_push(cpu_t * This, int * args, int size)
{
	ASSERTCPU(This);
	SIZECONTROL(1, cpu_push);
	assert(args);

	Stack_push(&This->stk, *args);

	ASSERTCPU(This);

	return 0;
}

int cpu_pop(cpu_t * This, int * args, int size) 
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_pop);

	int ret = Stack_pop(&This->stk);

	ASSERTCPU(This);

	return ret;
}
int cpu_add(cpu_t * This, int * args, int size) 
{ 
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_add);

	int sum1 = cpu_pop(This, NULL, 0);
	int sum2 = cpu_pop(This, NULL, 0);
	int sum = sum1 + sum2;

	cpu_push(This, &sum, 1);

	ASSERTCPU(This);

	return 0;
}
int cpu_mul(cpu_t * This, int * args, int size) 
{
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_add);

	int mul1 = cpu_pop(This, NULL, 0);
	int mul2 = cpu_pop(This, NULL, 0);
	int mul = mul1 * mul2;

	cpu_push(This, &mul, 1);

	ASSERTCPU(This);

	return 0; 
}
int cpu_sub(cpu_t * This, int * args, int size)
{ 
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_add);

	int sub1 = cpu_pop(This, NULL, 0);
	int sub2 = cpu_pop(This, NULL, 0);
	int sub = sub2 - sub1;

	cpu_push(This, &sub, 1);

	ASSERTCPU(This);

	return 0; 
}

int cpu_out(cpu_t * This, int * args, int size) 
{ 
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_out);

	printf("%d\n", cpu_pop(This, NULL, 0));

	ASSERTCPU(This);

	return 0; 
}

int cpu_jmp(cpu_t * This, int * args, int size) { return 0; } // Not realized yet

int cpu_exit(cpu_t * This, int * args, int size) 
{ 
	ASSERTCPU(This);
	SIZECONTROL(0, cpu_exit);

	system("pause");

	return 0; 
}