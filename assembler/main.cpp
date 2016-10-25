#include "main.h"

int main()
{
    char * AsmTxt = NULL;
    char * FName = NULL;

    FName = GetFName ();

    int _size = ReadAsm ( FName, &AsmTxt );
    while ( _size < 0 )
    {
        FName = GetFName ();
        _size = ReadAsm ( FName, &AsmTxt );
    }

    WriteObj ( AsmTxt, _size );

    free ( AsmTxt );
    free ( FName );

	system ( "pause" ); 

    return 0;
}

