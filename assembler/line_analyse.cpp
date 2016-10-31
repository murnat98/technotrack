#include "main.h"

int CheckOper(const char * oper, const char * cmd, int line)
{
	#define DEFCMD( name, num, OperCnt)    \
	if ( !_stricmp ( cmd, #name ) )        \
		return check_##name ( oper, line );           
	#include "cmds.h"	
	#undef DEFCMD

	return -1; //! Command not found
}		

int LineAnalyse(int * arr, const char * txt, int line)
{
	int TxtLen = strlen(txt);
	bool FstSpc = true, CmdDefined = false, brk = false;
	char * cmd = NULL;

	int SpcPos = DetCmd(&cmd, txt);
	int len = strlen(cmd) - 1;
	PRINTF("------%d\n", strlen ( txt ) );
	if (cmd[len] == ':') //! ignoring labels
	{
		free(cmd);
		cmd = NULL;
		if (len + 2 <= strlen(txt))
			SpcPos += DetCmd(&cmd, txt + len + 2) + 1;
		else
			return 0;
	}
	PRINTF("cmd = %s, lines[i] = %s\n", cmd, txt);

	int MaxOperCnt = 0, OperCnt = 0;

	if (!(CmdDefined = DefCmd(arr, &MaxOperCnt, cmd)))
		ERROR(_FILE_, line + 1, "no such command \"%s\"\n", cmd)

	char * oper = (char *)calloc(MAXOPER, sizeof(*oper));
	int opcount = 0, arg = 0;

	for (int j = SpcPos; j < TxtLen; j++)
	{
		if (txt[j] == ';')
		{
			brk = true;
		}

		if (txt[j] != ',' && txt[j] != ' ')
		{
			oper[opcount++] = txt[j];
		}
		if ((txt[j] != ',' && j == TxtLen - 1 || txt[j] == ',') || brk)
		{
			if (OperCnt + 1 > MaxOperCnt)
				ERROR(_FILE_, line + 1, "too much arguments in command \"%s\"", cmd)
			oper[opcount] = '\0';

			arg = CheckOper(oper, cmd, line);

			if (arg < 0)
				ERROR(_FILE_, line + 1, "argument \"%s\" is not valid", oper)
			else
				arr[++OperCnt] = arg;
			opcount = 0;
		}

		if (brk)
			break;
	}

	free(oper);
	free(cmd);

	return OperCnt + 1;
}

int DetCmd(char ** cmd, const char * txt)
{
	bool FstSpc = true, CmdDetected = false;
	int _count = 0, i = 0;
	int FstLetter = DeleteSpcs(txt);
	i += FstLetter;

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

int DeleteSpcs(const char * str)
{
	int offset = 0;

	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == ' ' || str[i] == '\t')
			offset++;
		else
			break;
	}

	return offset;
}