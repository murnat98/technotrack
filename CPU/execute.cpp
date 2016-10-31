#include "main.h"

int execute()
{
	int * ram = NULL;
	long size = 0;
	assert((size = ReadFile(&ram)) >= 0);

	cpu_t Cpu = {};
	cpu_ctor(&Cpu);

	int offset = 0;
	for (long pc = PROGSTART; pc < size; pc += offset + 1)
	{
		offset = DefOffset(ram[pc]);


		///! TODO: optimize offset
		switch (ram[pc])
		{
			#define DEFCMD( name, num, PC )								 \
		case num:														 \
		//! TODO: cp & CP ?!?!?!
			cpu_##name ( &Cpu, ram + pc + PC, offset );		   			 \
			break;
			#include "cmds.h"
			#undef DEFCMD
		default:
			fprintf(stderr, "Cannot define the command. Please contact to developers!\n");
			abort();
		}

		_cpu_dump(&Cpu);
	}

	cpu_dtor(&Cpu);
	free(ram);

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
		PRINTF("Cannot define program counter!\b");
		abort();
	}

	return ret;
}

long ReadFile(int ** arr)
{
	FILE * exe = fopen(EXENAME, "rb");

	long size = _filelength(_fileno(exe)) / sizeof(int);
	*arr = (int *)calloc(size, sizeof(*arr));
	
	if (fread(*arr, sizeof(int *), size, exe) != size)
	{
		printf("Cannot read from exe file!\nTry one more time\n");
		return -1;
	}

	fclose(exe);

	return size;
}
