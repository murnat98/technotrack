#include "include.h"

int main()
{
	int * program = NULL;
	long size = ReadProgram(&program);

	cpu_t _cpu = {};
	cpu_ctor(&_cpu);
	execute(program, &_cpu, size);

	cpu_dtor(&_cpu);
	free(program);

	system("pause");

	return 0;
}

long ReadProgram(int ** program)
{
	FILE * prg = fopen(EXENAME, "rb");

	long size = _filelength(_fileno(prg)) / 4;
	*program = (int *)calloc(size, sizeof(int));

	long CheckSize = fread(*program, sizeof(int), size, prg);
	assert(CheckSize == size);

	fclose(prg);

	return size;
}