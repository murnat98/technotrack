#include "main.h"

int cpu_ctor(cpu_t * This)
{
	assert(Stack_ctor(&This->stk));

	return 0;
}

int Stack_dtor(cpu_t * This)
{
	assert(Stack_dtor(&This->stk));

	return 0;
}

bool cpu_OK(cpu_t * This)
{
	return Stack_OK(&This->stk);
}

int cpu_dump(cpu_t * This)
{

}

int cpu_push(cpu_t * This, int CmdNum, int * args, int size)
{


	Stack_push(&This->stk, *args);

	return 0;
}