#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <io.h>

#define ASSERT( var, text ) if ( var < 0 ) { printf ( "%s", text); return -1; }

const char FNOVELNAM[] = "Shakespeare.txt";
const char FSORTNAME[] = "sorted.txt";

int welcome();

int  ReadToBuf(const char *, char **);
long filesize(int);

int CountStr(char *, int);
int DivideStrs(char **, char *, int, int);

int PrintStr(char **, int, const char *);

int CmpFirst(const void *, const void *);
int CmpLast(const void *, const void *);
int strcmplast(const char *, const char *);

int main()
{
	welcome();

	int size = 0;
	char * buf;

	size = ReadToBuf(FNOVELNAM, &buf);

	int nLines = CountStr(buf, size);
	char ** Strs = (char **)calloc(nLines * 2, sizeof(char *));
	DivideStrs(Strs, buf, nLines, size);

	qsort(Strs, nLines, sizeof(char *), CmpFirst);

	PrintStr(Strs, nLines, FSORTNAME);

	free(buf);
	free(Strs);

	return 0;
}

int welcome()
{
	printf("Shakespeare's novel sorting program\n");

	return 0;
}

int ReadToBuf(const char * FileName, char ** buf)
{
	FILE * novel = fopen(FileName, "r");
	assert(novel);

	int sz = _filelength(_fileno(novel));
	assert(sz >= 0);

	*buf = (char *)calloc(sz, sizeof(char));

	if (fread(*buf, sizeof(char), sz, novel) == sz)
		assert(!"Cannot read files from the file!");

	fclose(novel);

	return sz;
}

int CountStr(char * s, int len)
{
	char EndOfStr = '\n';
	char * point;
	int count = 1;
	while ((point = strrchr(s, EndOfStr)))
	{
		*point = '\0';
		count++;
	}

	return count;
}

int DivideStrs(char ** arr, char * buf, int lines, int slen)
{
	bool assign = false;
	int ArrCount = 0, pos = 0;

	for (int i = 0; i < slen; i++)
	{
		if (buf[i] == '\0')
		{
			assign = true;
		}
		if (assign)
		{
			arr[ArrCount] = buf + pos;
			pos = i + 1;
			assign = false;
			ArrCount++;
		}
	}

	return 0;
}

int CmpFirst(const void * a, const void * b)
{
	return strcmp(*(char **)a, *(char **)b);
}

int CmpLast(const void * a, const void * b)
{
	return strcmplast(*(char **)a, *(char **)b);
}

int strcmplast(const char * s1, const char * s2)
{
	const char * EndOfa = s1 + strlen(s1) - 1;
	const char * EndOfb = s2 + strlen(s2) - 1;
	while (EndOfa > s1 && EndOfb > s2)
	{
		char lc1 = tolower(*EndOfa);
		char lc2 = tolower(*EndOfb);

		if (!isalpha(lc1))
		{
			EndOfa--;
			if (!isalpha(lc2))
			{
				EndOfb--;
			}
			continue;
		}

		if (lc1 > lc2)
			return 1;
		if (lc2 > lc1)
			return -1;
		EndOfa--;
		EndOfb--;
	}

	return 0;
}

int PrintStr(char ** s, int len, const char * FileName)
{
	FILE * sort = fopen(FileName, "w");

	for (int i = 0; i < len; i++)
	{
		if (!strlen(s[i]))
			continue;
		fprintf(sort, "%s\n", s[i]);
	}

	fclose(sort);

	return 0;
}

