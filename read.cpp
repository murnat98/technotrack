#include "main.h"
//#include <io.h>

char * GetFName ()
{
    const int MAXFNAME = 256;
    char * FName = ( char * ) calloc ( MAXFNAME, sizeof ( * FName ) );

    fgets ( FName, MAXFNAME, stdin );
    FName[strlen ( FName ) - 1] = '\0'; // deleting space

    return FName;
}

int ReadAsm ( char * FName, char ** ReadTxt )
{
    FILE * masm = fopen ( FName, "r" );
    if ( !masm )
    {
        fprintf ( stderr, "Cannot open this file!!\nMay be it does not exist!\nTry one more time\n" );
        return -1;
    }

    //long FileLen = filelength ( _fileno ( masm ) );
    long FileLen = 25;//!!!!!!!!!!!!
    *ReadTxt = ( char * ) calloc ( FileLen, sizeof ( char ) );

    if ( fread ( ( char * ) *ReadTxt, sizeof ( char ), FileLen, masm ) == FileLen )
    {
        fprintf ( stderr, "Cannot read file! Try one more time!\n" );
        return -1;
    }

    fclose ( masm );

    return FileLen;
}
