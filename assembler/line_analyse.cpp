#include "include.h"

int assemble(char * Asm, int ** arr, long size)
{
	int ArrSize = 0;
	*arr = (int *)calloc(size, sizeof(int));

	int nLines = CountStr(Asm, size);
	char ** lines = (char **)calloc(nLines * 2, sizeof(char *));
	DivideStrs(lines, Asm, nLines, size);

	Stack_t labels = {};
	Stack_ctor(&labels, MAXLABELCOUNT);

	ArrSize = pass((const char **)lines, *arr, nLines, &labels);
	ArrSize = pass((const char **)lines, *arr, nLines, &labels);

	Stack_dtor(&labels);

	return ArrSize;
}

int pass(const char ** lines, int * arr, int nLines, Stack_t * labels)
{
	int pc = 0, MaxOperCnt = 0, OperCnt = 0;
	bool CmdDefined = false, LblDefined = false;
	char * word     = NULL;
	char * cmd      = (char *)calloc(MAXCMD, sizeof(char));
	char * cpylines = (char *)calloc(MAXCMD, sizeof(char));

	for (int i = 0; i < nLines; i++)
	{
		CmdDefined = false;
		LblDefined = false;
		OperCnt    = 0;
		cmd[0]     = '\0';

		strcpy(cpylines, lines[i]);
		word = strtok(cpylines, " \t");

		while (word)
		{
			if (word[0] == ';')
				break;
			LblDefined = DefLbl((const char *)word, CmdDefined, strlen(word), labels, pc, i);
			if (LblDefined)
			{
				word = strtok(NULL, " \t");
				continue;
			}

			ArrWriter(arr, word, pc, cmd, &OperCnt, &MaxOperCnt, &CmdDefined, i, labels);

			pc++;
			word = strtok(NULL, " \t");
		}
	}

	free(cpylines);
	free(cmd);

	return pc;
}

int ArrWriter(int * arr, const char * word, int pc, char * cmd, int * OperCnt, int * MaxOperCnt, bool * CmdDefined, int line, Stack_t * labels)
{
	if (!*CmdDefined) // Define command
	{
		*CmdDefined = DefCmd(arr, MaxOperCnt, word, pc);
		if (*CmdDefined)
			strcpy(cmd, word);
		else
			ERROR(_FILE_, line + 1, "arguments must be after command!\n");
	}
	else // Define arguments
	{
		*OperCnt++;
		if (*MaxOperCnt < *OperCnt)
			ERROR(_FILE_, line + 1, "command \"%s\" must have %d arguments\n", cmd, *MaxOperCnt);

		arr[pc] = CheckArgs(cmd, word, line, labels);
		if (arr[pc] == -2)
			assert(!"arr[pc] == -2 in CheckArgs!!!!\n");
	}

	return 0;
}

bool DefCmd(int * arr, int * MaxOperCnt, const char * cmd, int pc)
{
	bool CmdDefined = false;

	#define DEFCMD( name, num, Oper_Cnt )  \
	if ( !_stricmp ( cmd, #name ) )        \
	{				                       \
		arr[pc] = cmd_##name;              \
		*MaxOperCnt = Oper_Cnt;	           \
		CmdDefined = true;                 \
	}	
	#include "cmds.h"
	#undef DEFCMD

	return CmdDefined;
}

bool DefLbl(const char * word, bool CmdDefined, int len, Stack_t * labels, int pc, int line)
{
	if (CmdDefined && word[len - 1] == ':')
	{
		ERROR(_FILE_, line + 1, "Label must be before command not argument!\n");
	
		return false;
	}

	if (word[len - 1] == ':')
	{
		Label_t push = {};
		push.name = (char *)calloc(MAXLABELSIZE, sizeof(char));
		strcpy(push.name, word);
		push.name[len - 1] = '\0';
		push.ptr = pc;

		Stack_push(labels, push);

		free(push.name);

		return true;
	}

	return false;
}

int CheckArgs(const char * cmd, const char * arg, int line, Stack_t * labels)
{
	#define DEFCMD( name, num, args )						 \
	if ( !_stricmp ( cmd, #name ) )					    	 \
		return check_##name ( arg, line, labels );

	#include "cmds.h"

	#undef DEFCMD

	return -2;
}

int CountStr(char * s, int len)
{
	char EndOfStr = '\n';
	char * point;
	int _count = 1;

	while ((point = strrchr(s, EndOfStr)))
	{
		*point = '\0';
		_count++;
	}

	return _count;
}

int DivideStrs(char ** arr, const char * s, int lines, int slen)
{
	bool _assign = false;
	int ArrLen = 0, ArrCount = 0, pos = 0;
	for (int i = 0; i < slen; i++)
	{
		if (s[i] == '\0')
		{
			_assign = true;
		}
		if (_assign)
		{
			arr[ArrCount] = (char *)s + pos;
			pos = i + 1;
			_assign = false;
			ArrCount++;
		}
	}

	return 0;
}
