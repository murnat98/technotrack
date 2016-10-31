#include "main.h"

int CountStr ( char * s, int len )
{
	char EndOfStr = '\n';
	char * point;
	int _count = 1;

	while ( ( point = strrchr ( s, EndOfStr ) ) )
	{
		*point = '\0';
		_count++;
	}
	return _count;
}

int DivideStrs ( char ** arr, const char * s, int lines, int slen )
{
	bool _assign = false;
	int ArrLen = 0, ArrCount = 0, pos = 0;
	for ( int i = 0; i < slen; i++ )
	{
		if ( s[i] == '\0' )
		{
			_assign = true;
		}
		if ( _assign )
		{
			arr[ArrCount] = ( char * ) s + pos;
			pos = i + 1;
			_assign = false;
			ArrCount++;
		}
	}
	return 0;
}

#ifdef DEBUG
	#define $
#else
	#define $ continue;
#endif // DEBUG

//! TODO: divide functions
int WriteObj ( const char * text, long _size )
{
    const char OBJFILE[10] = "a.obj";
    FILE * obj = fopen ( OBJFILE, "wb" );

    int nLines = CountStr( ( char * ) text, _size );
    char ** lines = ( char ** ) calloc ( nLines * 2, sizeof ( char * ) );
	DivideStrs ( lines, text, nLines, _size );

	const int MAXOPER = 10;
	int _count = 0;
	int * WriteArr = ( int * ) calloc ( MAXOPER, sizeof ( * WriteArr ) );

//! TODO: make 1 function Pass()
	FirstPass((const char **)lines, nLines);
	LastPass(WriteArr, (const char **)lines, nLines, obj);

	free(WriteArr);
	free(lines);

	fclose(obj);

    return 0;
}
#undef DEBUG

int FirstPass(const char ** lines, int nLines)
{
	int nLabels = 0, WordsCounter = 0;
	bool LabelFound = false;
	char * label = (char *)calloc(MAXLABEL, sizeof(*label));

	for (int i = 0; i < nLines; i++)
	{
		LabelFound = FindLabels(lines[i], label, i);
		if (LabelFound)
		{
			strcpy(AllLabels->name, label);
			AllLabels->ptr = WordsCounter;
			AllLabels->nLabel++;
			PRINTF("=====%d %s\n", AllLabels->ptr, AllLabels->name);
		}

		WordsCounter += CountWords(lines[i]);
	}

	free(label);

	return 0;
}

int LastPass(int * WriteArr, const char ** lines, int nLines, FILE * obj)
{
	int _count = 0;

	for (int i = 0; i < nLines; i++)
	{
		_count = LineAnalyse(WriteArr, lines[i], i);

		for (int j = 0; j < _count; j++)
		{
			$
			printf("%d\n", WriteArr[j]);
		}

		if (fwrite(WriteArr, sizeof(*WriteArr), _count, obj) != _count)
		{
			fprintf(stderr, "Cannot read file! Try one more time!\n");
			return -1;
		}
	}

	return 0;
}

#define RETURN( ret )   \
free ( cstr );			\
return ret;
bool FindLabels(const char * str, char * label, int line)
{
	char * cstr = (char *)calloc(strlen(str) + 1, sizeof(*cstr));
	strcpy(cstr, str);

//! TODO: use sscanf()
	if (strpbrk(cstr, ":"))
	{
		strtok(cstr, ":");
		if (strpbrk(cstr, ":"))
		{
			ERROR(_FILE_, line + 1, "there are 2 or more labels in one line\n");
		}

		PRINTF("%s\n", cstr);
		strcpy(label, cstr);

		RETURN(true);
	}
	else
	{
		strcpy(label, "");

		RETURN(false);
	}

	RETURN(true); //! just for no warnings
}
#undef RETURN

int CountWords(const char * str)
{
	int counter = 0;
	char * cstr = (char *)calloc(strlen(str) + 1, sizeof(*cstr));

	strcpy(cstr, str);
	int offset = DeleteSpcs(cstr);
	cstr += offset;

	char * pch = strtok(cstr, " ");

	while (pch)
	{
		if (strpbrk(pch, ";"))
			break;

		if (pch[strlen(pch) - 1] != ':') //! if no label
			counter++;

		pch = strtok(NULL, " ");
	}

	cstr -= offset;
	free(cstr);

	return counter;
}
