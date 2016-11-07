#include "include.h"

int execute(const int * prg, cpu_t * _cpu, long size)
{
	int offset = 0;
	for (_cpu->pc = PROGSTART; _cpu->pc < size; _cpu->pc += offset + 1)
	{
		_cpu_dump(_cpu);
		offset = DefOffset(prg[_cpu->pc]);
		switch (prg[_cpu->pc])
		{
		#define DEFCMD( name, num, args )														 \
		case num:																				 \
			offset = cpu_##name ( _cpu, prg + _cpu->pc + args, offset );	   					 \
			break;

			#include "cmds.h"

			#undef DEFCMD
		default:
			fprintf(stderr, "Cannot define the command. Please, contact to developers!\n");
			abort();
		}
	}

	return 0;
}

int DefOffset(int CmdNum)
{
	int ret = -1;
	#define DEFCMD( name, num, pc ) \
	if ( num == CmdNum )            \
		ret = pc;
	#include "cmds.h"
	#undef DEFCMD

	if (ret == -1)
	{
		PRINTF("Cannot define program counter!\n");
		printf("Something went wrong!!\nContact with developers\n");
		abort();
	}

	return ret;
}