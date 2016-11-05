#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

//==========DEFINES========
#define DEBUG
#define ERROR( txt, error_val ) printf ( "%s", txt ); This -> error = error_val;
#define WARNING( txt ) ERROR ( txt, 0 )

#ifndef NDEBUG
    #define ASSERT( stk ) if ( !Stack_OK ( stk ) ) { _Stack_dump ( stk ); assert ( !"Stack si not OK!!!\n" ); }
    #define _Stack_dump( stk ) Stack_dump ( stk, #stk );
#else
    #define ASSERT( stk )
    #define _Stack_dump( stk )
#endif // DEBUG

//!=========TYPES======
typedef int type;
typedef struct Stack
{
	type * data;
	int count;
	int error;
	int max_elem;
	bool allocated = false;
} Stack_t;

//!=============CONSTANTS===========
const int    ERROR_POISON = -666;
const int    COUNT_POISON = -666;
const int    DATA_POISON  = -666;

//!=============FUNCTIONS============
int  Stack_ctor   ( Stack_t *, size_t );
int  Stack_dtor   ( Stack_t * );
bool Stack_OK     ( const Stack_t * );
int  Stack_dump   ( const Stack_t *, const char * );
int  Stack_push   ( Stack_t *, type );
type Stack_pop    ( Stack_t * );
int  Stack_repush ( Stack_t *, type );

#endif // STACK_H_INCLUDED
