#include "main.h"

Label_t * AllLabels;
char _FILE_[FILENAME_MAX] = "";

int main()
{
	setlocale(LC_ALL, "Russian");

    char * AsmTxt = NULL;
    char * FName = NULL;

	AllLabels = Label_new(MAXLABELCOUNT, MAXLABELSIZE);

    FName = GetFName ();

    int _size = ReadAsm ( FName, &AsmTxt );
    while ( _size < 0 )
    {
        FName = GetFName ();
        _size = ReadAsm ( FName, &AsmTxt );
    }
	strcpy(_FILE_, FName);

	//! TODO: divide this on 2 functions.
    WriteObj ( AsmTxt, _size );
	printf("Build Ok!\n");

    free ( AsmTxt );
    free ( FName );

	Label_delete(AllLabels);

	system ( "pause" );

    return 0;
}
