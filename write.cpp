#include "main.h"

int CountStr ( char * s, int len )
{
	char EndOfStr = '\n';
	char * point;
	int _count = 0;
	while ( ( point = strrchr ( s, EndOfStr ) ) )
	{
		* ( point - 0 ) = '\0';
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
			//ArrLen = i - pos; //!!!!!! comment after
		}
		if ( _assign )
		{
			//arr[ArrCount] = ( char * ) calloc ( ArrLen, sizeof ( char ) ); //!!!!!!!!!!! comment after
			arr[ArrCount] = ( char * ) s + pos;
			printf ( "i = %d; pos = %d\n", i, pos );
			pos = i + 1;
			_assign = false;
			ArrCount++;
		}
	}
	return 0;
}

int LineAnalyse ( const int * arr, const char * txt )
{
    int TxtLen = strlen ( txt ), _count = 0, cmd_count = 0;
    bool FstSpc = true;
    char * cmd = ( char * ) calloc ( MAXCMD, sizeof ( * cmd ) );

    for ( int i = 0; i < TxtLen; i++ )
    {
        switch ( txt[i] )
        {
        case ' ':
            if ( FstSpc )
            {
                cmd[_count] = '\0';
                //printf ( "%s\n", cmd );
                FstSpc = false;
            }
            break;
        default:
            if ( FstSpc )
            {
                cmd[_count++] = txt[i];
            }
        }
    }

    free ( cmd );

    return cmd_count;
}

int WriteObj ( const char * text, long _size )
{
    const char OBJFILE[10] = "a.out";
    FILE * obj = fopen ( OBJFILE, "wb" );

    for ( int i = 0; i < _size; i++ )
        printf ( "%d\n", text[i] );
    printf ( "===============\n" );
    int nLines = CountStr( ( char * ) text, _size );
    for ( int i = 0; i < _size; i++ )
        printf ( "%d\n", text[i] );
    char ** lines = ( char ** ) calloc ( nLines, sizeof ( char * ) );
	DivideStrs ( lines, text, nLines, _size );

	const int MAXOPER = 10;
	int _count = 0;
	//int * WriteArr = ( int * ) calloc ( MAXOPER, sizeof ( * WriteArr ) );


	for ( int i = 0; i < nLines; i++ )
    {
        //printf ( "%s\n", lines[i] );
        //_count = LineAnalyse ( WriteArr, lines[i] );
        /*if ( fwrite ( ( int * ) WriteArr, sizeof ( * WriteArr ), _count, obj ) == _cpunt )
        {
            fprintf ( stderr, "Cannot read file! Try one more time!\n" );
            return -1;
        }*/
    }

    //free ( WriteArr );
    free ( lines );

    fclose ( obj );

    return 0;
}
