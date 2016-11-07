#include "include.h"

char _FILE_[FILENAME_MAX] = "";

int main()
{
	setlocale(LC_ALL, "Russian");

	char * AsmTxt   = NULL;
	char * FName    = NULL;
	int  * WriteArr = NULL;

	printf("MyAssembler compiler\nInput *.masm file name:\n");
	GetFName (&FName);

	int _size = ReadAsm ( FName, &AsmTxt );
	while ( _size < 0 )
	{
		GetFName (&FName);
		_size = ReadAsm ( FName, &AsmTxt );
	}
	strcpy(_FILE_, FName);

	int WriteSize = assemble(AsmTxt, &WriteArr, _size);
	WriteObj(WriteArr, WriteSize);
	printf("Build Ok!\n");

	free (AsmTxt);
	free (WriteArr);
	free (FName);

	system("pause"); 

    return 0;
}

