#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#define ASSERT( var, text ) if ( var < 0 ) { printf ( "%s", text); return -1; }

const char FNOVELNAM[] = "Shakespeare.txt";
const char FSORTNAME[] = "sorted.txt";

int welcome ();
long filesize ( int );
int ReadToBuf ( char *, int, int );
int CountStr ( char *, int );
int ClearVoidLines ( char * );
int DivideStrs ( char **, char *, int, int );
int PrintStr ( char **, int, FILE * );
int CmpFirst ( const void *, const void * );
int CmpLast ( const void *, const void * );
int strcmplast ( const char *, const char * );

int main()
{
	FILE * novel = fopen ( FNOVELNAM, "r" );
	assert ( novel );
	FILE * sort = fopen ( FSORTNAME, "w" );
	assert ( sort );
	
	welcome ();
	
	long size = filesize ( fileno ( novel ) );
	ASSERT ( size, "Cannot define file size!!!\nTry one more time\n" );
	char * buf = ( char * ) calloc ( size, sizeof ( buf ) );
	ASSERT ( ReadToBuf ( buf, fileno ( novel ), size ), "Cannot read from file!!!\nTry one more time\n" );

	int nLines = CountStr( buf, size );
	char ** Strs = ( char ** ) calloc ( nLines, sizeof ( char * ) );
	DivideStrs ( Strs, buf, nLines, size );

	qsort ( Strs, nLines, sizeof ( char * ), CmpFirst );

	PrintStr ( Strs, nLines, sort );

	fclose ( novel );
	fclose ( sort );

	free ( buf );
	free ( Strs );
	return 0;
}

int welcome ()
{
	printf ( "Shakespeare's novel sorting program\n" );
}

long filesize ( int fd )
{
	struct stat fl;
	if ( fstat ( fd, &fl ) == -1 )
	{
		printf ( "Cannot get file size!!!\nTry one more time!\n" );
		return -1;
	}
	return fl.st_size;
}

int ReadToBuf ( char * str, int fd, int len )
{
	if ( read ( fd, str, len ) != len )
	{
		printf ( "Cannot read files from \"%s\"!!!\nTry one more time!\n", FNOVELNAM );
		return -1;
	}
	return 0;
}
	
int CountStr ( char * s, int len )
{
	char EndOfStr = '\n';
	char * point;
	int count = 0;
	while ( ( point = strrchr ( s, EndOfStr ) ) )
	{
		*point = '\0';
		count++;
	}
	return count;
}

int DivideStrs ( char ** arr, char * s, int lines, int slen )
{
	bool assign = false;
	int ArrLen = 0, ArrCount = 0, pos = 0;
	for ( int i = 0; i < slen; i++ )
	{
		if ( s[i] == '\0' )
		{
			assign = true;
			ArrLen = i - pos;
		}
		if ( assign )
		{
			arr[ArrCount] = ( char * ) calloc ( ArrLen, sizeof ( char ) );
			arr[ArrCount] = s + pos;
			pos = i + 1;
			assign = false;
			ArrCount++;
		}
	}
	return 0;
}

int CmpFirst ( const void * a, const void * b )
{
	return strcasecmp ( * ( char ** ) a, * ( char ** ) b );
}

int CmpLast ( const void * a, const void * b )
{
	return strcmplast ( * ( char ** ) a, * ( char ** ) b );
}

int strcmplast ( const char * s1, const char * s2 )
{
	const char * EndOfa = s1 + strlen ( s1 ) - 1;
	const char * EndOfb = s2 + strlen ( s2 ) - 1;
	while ( EndOfa > s1 && EndOfb > s2 )
	{
		char lc1 = tolower ( *EndOfa );
		char lc2 = tolower ( *EndOfb );
		if ( !isalpha ( lc1 ) && isalpha ( lc2 ) )
		{
			EndOfa--;
			continue;
		}
		if ( isalpha ( lc1 ) && !isalpha ( lc2 ) )
		{
			EndOfb--;
			continue;
		}
		if ( !isalpha ( lc1 ) && !isalpha ( lc2 ) )
		{
			EndOfa--;
			EndOfb--;
			continue;
		}
		if ( lc1 > lc2 )
			return 1;
		if ( lc2 > lc1 )
			return -1;
		EndOfa--;
		EndOfb--;
	}
	return 0;
}

int PrintStr ( char ** s, int len, FILE * stream )
{
	for ( int i = 0; i < len; i++ )
	{
		if ( !strlen ( s[i] ) )
			continue;
		fprintf ( stream, "%s\n", s[i] );
	}
	return 0;
}
