#include "include.h"

int WriteObj ( const int * arr, int _size )
{
    const char OBJFILE[10] = "a.obj";
    FILE * obj = fopen ( OBJFILE, "wb" );

	for (int i = 0; i < _size; i++)
		printf("%d ", arr[i]);

	fwrite(arr, _size, sizeof(int), obj);

	fclose(obj);

    return 0;
}
