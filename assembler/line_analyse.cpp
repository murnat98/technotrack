#include "main.h"

int CheckOper(const char * oper, const char * cmd)
{

	return 0;
}			            

int LineAnalyse(int * arr, const char * txt, int line, const char * _FILE_)
{
	int TxtLen = strlen(txt), cmd_count = 0;
	bool FstSpc = true, CmdDefined = false;
	char * cmd = NULL;

	int SpcPos = DetCmd(&cmd, txt);
	printf("cmd = %s\n", cmd);

	int MaxOperCnt = 0, OperCnt = 0;

	if (!(CmdDefined = DefCmd(arr, &MaxOperCnt, cmd)))
		ERROR(_FILE_, line + 1, "no such command %s\n", cmd);

	char * oper = (char *)calloc(MAXOPER, sizeof(*oper));
	int opcount = 0;

	for (int j = SpcPos; j < TxtLen; j++)
	{
		if (txt[j] != ',')
		{
			oper[opcount++] = txt[j];
		}
		if (txt[j] != ',' && j == TxtLen - 1 || txt[j] == ',')
		{
			if (OperCnt + 1 > MaxOperCnt)
				ERROR(_FILE_, line + 1, "too much opends in command \"%s\"", cmd);
			oper[opcount] = '\0';
			if (CheckOper(oper, cmd) < 0)
				ERROR(_FILE_, line + 1, "Operand \"%s\" is not valid", oper);
			arr[++OperCnt] = atoi(oper);
			opcount = 0;
		}
	}

	free(oper);
	free(cmd);

	return OperCnt + 1;
}
#undef DEFCMD
#undef IF_SPACE

int DetCmd(char ** cmd, const char * txt)
{
	bool FstSpc = true, CmdDetected = false;
	int _count = 0, i = 0;
	*cmd = (char *)calloc(MAXCMD, sizeof(char));

	while (txt[i] != ' ' && txt[i] != '\0')
	{
		switch (txt[i])
		{
		case ' ':
			if (FstSpc)
			{
				cmd[0][_count] = '\0';
				FstSpc = false;
			}
			CmdDetected = true;
			break;

		default:
			if (FstSpc)
			{
				cmd[0][_count++] = txt[i];
			}
		}

		i++;
	}

	if (!CmdDetected)
		cmd[0][_count] = '\0';

	return i;
}

bool DefCmd(int * arr, int * MaxOperCnt, const char * cmd)
{
	bool CmdDefined = false;

	#define DEFCMD( name, num, Oper_Cnt )  \
	if ( !_stricmp ( cmd, #name ) )        \
	{				                       \
		arr[0] = cmd_##name;               \
		*MaxOperCnt = Oper_Cnt;	           \
		CmdDefined = true;                 \
	}	
	#include "cmds.h"	
	#undef DEFCMD

	return CmdDefined;
}