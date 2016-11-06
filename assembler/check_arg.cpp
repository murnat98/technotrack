#include "include.h"

bool IsNum(const char * str)
{
	for (size_t i = 0; i < strlen(str); i++)
	{
		if (isalpha(str[i]))
		{
			return false;
		}
	}

	return true;
}

int check_push(const char * arg, int line, Stack_t * labels )
{
	if (!IsNum(arg))
	{
		WARNING(_FILE_, line + 1, "arguments in \"push\" must be a number\n")
	}

	return atoi ( arg );
}

int check_jmp(const char * arg, int line, Stack_t * labels)
{
	if (!IsNum(arg))
	{
		if (!isalpha(arg[0]) && arg[0] != '.' )
			ERROR(_FILE_, line + 1, "arguments in \"jmp\" must be either label or address\n")
		else //! it is label
		{
			return Stack_find ( labels, arg ); //! return address
		}
	}
	else //! it is address
	{
		return atoi ( arg );
	}

	return 0;
}

int check_pop (const char * arg, int line, Stack_t * labels) { return 0; }
int check_add (const char * arg, int line, Stack_t * labels) { return 0; }
int check_mul (const char * arg, int line, Stack_t * labels) { return 0; }
int check_sub (const char * arg, int line, Stack_t * labels) { return 0; }
int check_out (const char * arg, int line, Stack_t * labels) { return 0; }
int check_exit(const char * arg, int line, Stack_t * labels) { return 0; }