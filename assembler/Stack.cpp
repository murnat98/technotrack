#include "include.h"

int Stack_ctor ( Stack_t * This, size_t size )
{
	assert ( This );

	if ( This -> allocated )
	{
		if ( size <= This -> max_elem )
		{
			WARNING_ ( "Stack is already allocated of more size than requested!\n" )
			return -1;
		}
		This -> data = ( type * ) realloc ( ( type * ) This -> data, size * sizeof ( * This -> data ) );

		for (int i = This->count; i < size; i++)
		{
			strcpy(This->data[i].name, "POISON");
			This->data[i].ptr = DATA_POISON;
		}

		This -> max_elem = size;

		return 0;
	}
	else
	{
		This->data = Label_new(MAXLABELCOUNT, MAXLABELSIZE);
		This->allocated = true;

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
		WARNING_ ( "Stack is already freed!\n" )
		return -1;
	}
	Label_delete(This->data);
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

	for ( int i = 0; i < This -> max_elem; i++ )
	{
		if (i < This->count)
		{
			fprintf(dump, "\t\t*[%d] = %s\n", i, This->data[i].name);
			fprintf(dump, "\t\t*[%d] = %d\n", i, This->data[i].ptr);
		}
		else
		{
			fprintf(dump, "\t\t[%d] = %s\tPoison!\n", i, This->data[i].name);
			fprintf(dump, "\t\t[%d] = %d\tPoison!\n", i, This->data[i].ptr);
		}
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
		WARNING_ ("Segmentation fault\n");
		abort();
		return -1;
	}
	strcpy(This->data[This->count].name, val.name);
	This->data[This->count].ptr = val.ptr;
	This -> count++;

	ASSERT ( This );

	return 0;
}

type Stack_pop ( Stack_t * This )
{
	ASSERT ( This );

	if ( !This -> count ) // Empty stack
	{
		WARNING_("Segmentation fault\n")
		abort();
	}

	This -> count--;
	type ret = This -> data[This -> count];
	strcpy(This->data[This->count].name, CHAR_POISON);
	This->data[This->count].ptr = DATA_POISON;

	ASSERT ( This );

	return ret;
}

int Stack_find(const Stack_t * This, const char * LblName)
{
	ASSERT(This);

	for (int i = 0; i < This->count; i++)
	{
		if (!_stricmp(This->data[i].name, LblName))
		{
			return This->data[i].ptr;
		}
	}

	ASSERT(This);

	return -1;
}
