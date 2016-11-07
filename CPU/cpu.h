#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include "Stack.h"

//!=============DEFINES=============
#ifndef NDEBUG
	#define ASSERTCPU( Cpu ) if ( !cpu_OK ( Cpu ) ) { _cpu_dump ( Cpu ); assert ( !"Stack is not OK!!!\n" ); }
	#define _cpu_dump( Cpu ) cpu_dump ( Cpu, #Cpu );
	#define SIZECONTROL( SizeVal, func )				 \
	if ( size != SizeVal )								 \
	{													 \
		PRINTF("Bad size value in %s", #func);			 \
		abort();										 \
	}
#else
	#define ASSERTCPU( Cpu )
	#define _cpu_dump( Cpu )
	#define SIZECONTROL( SizeVal, func )
#endif // NDEBUG


//!============CONSTANTS============
const int STACK_SIZE = 1000;
const int REGPOISON  = -666;
const int PCPOISON   = -1;

//!==============TYPES==============
typedef struct CPU
{
	Stack_t stk;
	int ax;
	int bx;
	int cx;
	int dx;
	long pc;
} cpu_t;

//!============FUNCTIONS============
#define DEFCMD( name, num, pc ) \
int cpu_##name ( cpu_t *, const int *, int );
#include "cmds.h"
#undef DEFCMD
int  cpu_ctor (cpu_t *);
int  cpu_dtor (cpu_t *);
bool cpu_OK   (const cpu_t *);
int  cpu_dump (const cpu_t *, const char *);

#endif // CPU_H_INCLUDED