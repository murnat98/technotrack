#include "include.h"

#ifdef DEBUG
	#define $
#else
	#define $ continue;
#endif // DEBUG
int WriteObj ( const int * arr, int _size )
{
    const char OBJFILE[10] = "a.obj";
    FILE * obj = fopen ( OBJFILE, "wb" );

	fwrite(arr, _size, sizeof(int), obj);

	fclose(obj);

    return 0;
}
#undef DEBUG