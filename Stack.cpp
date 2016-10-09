#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//==========DEFINES========
#define ERROR( txt, error_val ) printf ( "%s", txt ); This -> error = error_val;
#define WARNING( txt ) ERROR ( txt, 0 )
#define _ assert ( Stack_OK ( This ) );

//=========TYPES======
typedef double type;
typedef struct Stack
{
	type * data;
	int count;
	int error;
	int max_elem;
	bool allocated = false;
} Stack_t;

//=============CONSTANTS===========
const int    ERROR_POISON = -666;
const int    COUNT_POISON = -666;
const double DATA_POISON  = -666;

//=============FUNCTIONS============
int Stack_ctor   ( Stack_t *, size_t );
int Stack_dtor   ( Stack_t * );
bool Stack_OK    ( const Stack_t * );
int Stack_dump   ( const Stack_t * );
int Stack_push   ( Stack_t *, type );
type Stack_pop   ( Stack_t * );
int Stack_repush ( Stack_t *, type );

int main()
{
	Stack_t stk;
	Stack_ctor ( &stk, 10 );
	for ( int i = 0; i < 11; i++ )
		Stack_push ( &stk, i + 1 );
	Stack_dump ( &stk );
	for ( int i = 0; i < 11; i++ )
		printf ( "%lg\n", Stack_pop ( &stk ) );
	Stack_dump ( &stk );
	Stack_dtor ( &stk );
	return 0;
}

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
	This -> data = ( type * ) calloc ( size, sizeof ( * This -> data ) );
	This -> allocated = true;

	for ( int i = 0; i < size; i++ )
		This -> data[i] = DATA_POISON;
	
	This -> max_elem = size;
	
	This -> count = 0;
	This -> error = 0;
	return 0;
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

const char DUMPFILENAM[] = "dump.txt";
int Stack_dump ( const Stack_t * This )
{
	char ok_txt[10];
	if ( Stack_OK ( This ) )
		strcpy ( ok_txt, "Ok" );
	else
		strcpy ( ok_txt, "ERROR" );
	
	FILE * dump = fopen ( DUMPFILENAM, "a+" );
	
	fprintf ( dump, "Stack_t \"stk\" (%s) [%p]\n", ok_txt, This );
	fprintf ( dump, "{\n\tdata[%d] = [%p]\n", This -> max_elem, This -> data );
	fprintf ( dump, "\t{\n" );
	for ( int i = 0; i < This -> max_elem; i++ )
	{
		if ( i < This -> count )
			fprintf ( dump, "\t\t*[%d] = %lg\n", i, This -> data[i] );
		else
			fprintf ( dump, "\t\t[%d] = %lg     Poison!\n", i, This -> data[i] );
	}
	fprintf ( dump, "\t}\n\tcount = %d\n", This -> count );
	fprintf ( dump, "\terror= %d\n", This -> error );
	fprintf ( dump, "\tmax_elem = %d\n", This -> max_elem );
	fprintf ( dump, "}\n" );

	fclose ( dump );
}

int Stack_push ( Stack_t * This, type val )
{_
	if ( This -> count >= This -> max_elem ) // Full stack
	{
		WARNING ( "Cannot push the elements to stack, it is full!\nDo you want to increase the size of the stack? (y/n)\n" )
		Stack_repush ( This, val );
		return -1;
	}
	This -> data[This -> count] = val;
	This -> count++;
	return 0;
_}

type Stack_pop ( Stack_t * This )
{_
	if ( !This -> count ) // Empty stack
	{
		WARNING ( "Cannot pop elements from stack, it is empty!\n" )
		return DATA_POISON;
	}
	
	This -> count--;
	type ret = This -> data[This -> count];
	This -> data[This -> count] = DATA_POISON;
	return ret;
_}

int Stack_repush ( Stack_t * This, type val )
{_
	char answer;
	answer = getchar ();
	switch ( answer )
	{
	case 'y':
		Stack_ctor ( This, This -> max_elem * 2 );
		Stack_push ( This, val );
		break;	
	case 'n':
		break;
	default:
		printf ( "Enter yes (y) or no (n):\n" );
		Stack_repush ( This, val );
		return 0;
	}
	return 0;
_}
