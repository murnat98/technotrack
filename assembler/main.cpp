#include "main.h"

int main()
{
	setlocale(LC_ALL, "Russian");
    char * AsmTxt = NULL;
    char * FName = NULL;

    FName = GetFName ();

    int _size = ReadAsm ( FName, &AsmTxt );
    while ( _size < 0 )
    {
        FName = GetFName ();
        _size = ReadAsm ( FName, &AsmTxt );
    }

    WriteObj ( AsmTxt, _size, FName );

    free ( AsmTxt );
    free ( FName );

	system ( "pause" ); 

    return 0;
}

