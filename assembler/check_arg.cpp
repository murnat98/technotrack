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

int check_pushc(const char * arg, int line, Stack_t * labels )
{
	if (!IsNum(arg))
	{
		WARNING(_FILE_, line + 1, "arguments in \"pushc\" must be a number\n")
	}

	return atoi ( arg );
}

#define DEFREG( reg, regnum ) \
if ( !_stricmp ( #reg, arg ) ) \
	return regnum;
int check_pushr(const char * arg, int line, Stack_t * labels)
{
	DEFREG(ax, 1)
	DEFREG(bx, 2)
	DEFREG(cx, 3)
	DEFREG(dx, 4)

	WARNING ( _FILE_, line + 1, "arguments in \"%s\" must registers!!!\n", arg)

	return 0;
}
#undef DEFREG

int check_popr(const char * arg, int line, Stack_t * labels)
{
	return check_pushr(arg, line, labels);
}

int check_jmp(const char * arg, int line, Stack_t * labels)
{
	return check_jmpf(arg, line, labels);
}

int check_jmpf(const char * arg, int line, Stack_t * labels)
{
	if (!IsNum(arg))
	{
		if (!isalpha(arg[0]) && arg[0] != '.' )
			ERROR(_FILE_, line + 1, "arguments in \"jmp\" must be either label or address\n")
		else //! it is label
			return Stack_find ( labels, arg ); //! return address
	}
	else //! it is address
	{
		return atoi ( arg );
	}

	return 0;
}

int check_call(const char * arg, int line, Stack_t * labels)
{
	return check_jmpf(arg, line, labels);
}

int check_pop   (const char * arg, int line, Stack_t * labels) { return 0; }

int check_add   (const char * arg, int line, Stack_t * labels) { return 0; }
int check_sub   (const char * arg, int line, Stack_t * labels) { return 0; }
int check_mul   (const char * arg, int line, Stack_t * labels) { return 0; }
int check_div   (const char * arg, int line, Stack_t * labels) { return 0; }

int check_ret   (const char * arg, int line, Stack_t * labels) { return 0; }

int check_equal (const char * arg, int line, Stack_t * labels) { return 0; }
int check_noteq (const char * arg, int line, Stack_t * labels) { return 0; }
int check_boreq (const char * arg, int line, Stack_t * labels) { return 0; }
int check_aoreq (const char * arg, int line, Stack_t * labels) { return 0; }
int check_below (const char * arg, int line, Stack_t * labels) { return 0; }
int check_above (const char * arg, int line, Stack_t * labels) { return 0; }
int check_and   (const char * arg, int line, Stack_t * labels) { return 0; }
int check_or    (const char * arg, int line, Stack_t * labels) { return 0; }
int check_not   (const char * arg, int line, Stack_t * labels) { return 0; }

int check_in    (const char * arg, int line, Stack_t * labels) { return 0; }
int check_out   (const char * arg, int line, Stack_t * labels) { return 0; }

int check_exit  (const char * arg, int line, Stack_t * labels) { return 0; }