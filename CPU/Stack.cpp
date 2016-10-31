#include "main.h"

int Stack_ctor ( Stack_t * This, size_t size )
{
	assert ( This );

	if ( This -> allocated )
	{
		if ( size <= This -> max_elem )
		{
			WARNING ( "Stack is already allocated of more size than requested!\n" )
			return -1;
		}
		This -> data = ( type * ) realloc ( ( type * ) This -> data, size * sizeof ( * This -> data ) );

		for ( int i = This -> count; i < size; i++ )
			This -> data[i] = DATA_POISON;

		This -> max_elem = size;

		return 0;
	}
	else
	{
		This->data = (type *)calloc(size, sizeof(*This->data));
		This->allocated = true;

		for (int i = 0; i < size; i++)
			This->data[i] = DATA_POISON;

		This->max_elem = size;

		This->count = 0;
		This->error = 0;

		return 0;
	}
}

int Stack_dtor ( Stack_t * This )
{
	assert ( This );

	if ( !This -> allocated )
	{
		WARNING ( "Stack is already freed!\n" )
		return -1;
	}
	free ( This -> data );
	This -> data = NULL;
	This -> allocated = false;

	This -> max_elem = 0;
	This -> error = ERROR_POISON;
	This -> count = COUNT_POISON;

	return 0;
}

bool Stack_OK ( const Stack_t * This )
{
	return This &&
	       This -> allocated &&
	       This -> data &&
 	       ( This -> count >= 0 ) &&
	       !This -> error &&
	       This -> max_elem &&
	       This -> count <= This -> max_elem;
}

const char DUMPFILENAM[] = "stack.dump";
int Stack_dump ( const Stack_t * This, const char * VarName )
{
	char ok_txt[10];
	if ( Stack_OK ( This ) )
		strcpy ( ok_txt, "Ok" );
	else
	{
		strcpy(ok_txt, "ERROR");
		assert(This);
		assert(This->data);
	}

	FILE * dump = fopen ( DUMPFILENAM, "a+" );

	fprintf ( dump, "Stack_t \"%s\" (%s) [%p]\n", VarName, ok_txt, This );
	fprintf ( dump, "{\n\tdata[%d] = [%p]\n", This -> max_elem, This -> data );
	fprintf ( dump, "\t{\n" );

	for ( int i = 0; i < This -> count; i++ )
	{
		if ( i < This -> count )
			fprintf ( dump, "\t\t*[%d] = %d\n", i, This -> data[i] );
		else
			fprintf ( dump, "\t\t[%d] = %d     Poison!\n", i, This -> data[i] );
	}

	fprintf ( dump, "\t}\n\tcount = %d\n", This -> count );
	fprintf ( dump, "\terror = %d\n", This -> error );
	fprintf ( dump, "\tmax_elem = %d\n", This -> max_elem );
	fprintf ( dump, "}\n" );

	fclose ( dump );

	return 0;
}

int Stack_push ( Stack_t * This, type val )
{
	ASSERT ( This );

	if ( This -> count >= This -> max_elem ) // Full stack
	{
		WARNING("Segmentation fault\n");
		abort();
		return -1;
	}
	This -> data[This -> count] = val;
	This -> count++;

	ASSERT ( This );

	return 0;
}

type Stack_pop ( Stack_t * This )
{
	ASSERT ( This );

	if ( !This -> count ) // Empty stack
	{
		WARNING("Segmentation fault\n")
		abort();
		return DATA_POISON;
	}

	This -> count--;
	type ret = This -> data[This -> count];
	This -> data[This -> count] = DATA_POISON;

	ASSERT ( This );

	return ret;
}
