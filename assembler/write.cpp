#include "main.h"

int CountStr ( char * s, int len )
{
	char EndOfStr = '\n';
	char * point;
	int _count = 1;
	while ( ( point = strrchr ( s, EndOfStr ) ) )
	{
		* point = '\0';
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

#define DEBUG
#ifdef DEBUG
	#define $
#else
	#define $ continue;
#endif // DEBUG
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


	for ( int i = 0; i < nLines; i++ )
    {
        _count = LineAnalyse ( WriteArr, lines[i], i );

		for ( int j = 0; j < _count; j++ )
		{
			$
			printf ( "%d\n", WriteArr[j] );
		}

        if ( fwrite ( ( int * ) WriteArr, sizeof ( * WriteArr ), _count, obj ) != _count )
        {
            fprintf ( stderr, "Cannot read file! Try one more time!\n" );
            return -1;
        }
    }

    free ( WriteArr );
    free ( lines );

    fclose ( obj );

    return 0;
}
#undef DEBUG
