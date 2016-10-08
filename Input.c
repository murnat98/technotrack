#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
char * EofFgets ( char *, int, FILE * );
int Input1 ( char *, int );
char * Input2 ( int );
char * Input3 ( int );
int main()
{	
	const char MAX_LEN = 100;
	char * s = Input3 ( MAX_LEN );
	printf ( "%s\n", s );
	free ( s );
	return 0;
}
char * EofFgets ( char * s, int len, FILE * stream )
{
	fgets ( s, len, stream );
	char * lastsym;
	lastsym = s + strlen ( s ) - 1;
	if ( *lastsym == '\n' )
	{
		*lastsym = '\0';
		return s;
	}
	else if ( *lastsym == EOF )
	{
		return s;		
	}
	else
		return s;
}
int Input1 ( char * s, int len )
{
	EofFgets ( s, len, stdin );
	return 0;
}
char * Input2 ( int len )
{
	static char s[10] = "";
	EofFgets ( s, 10, stdin );
	return s;
}
char * Input3 ( int len )
{
	char * s = ( char * ) calloc ( len, sizeof ( * s ) );
	EofFgets ( s, len, stdin );
	assert ( s );
	return s;
}
