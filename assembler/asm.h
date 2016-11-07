#ifndef ASM_H_INCLUDED
#define ASM_H_INCLUDED

//!============CONSTANTS===========
const int MAXCMD = 10;
const int MAXOPER = 10;
enum cmds
{
	#define DEFCMD( name, num, ... ) cmd_##name = num,
	#include "cmds.h"
	#undef DEFCMD
	cmd_last
};

//!============FUNCTIONS===========
char * GetFName    ();
int    ReadAsm     ( char *, char ** );

int    CountStr    ( char *, int );
int    DivideStrs  ( char **, const char *, int, int );
int    LineAnalyse ( int *, const char *, int );
int    WriteObj    ( const char *, long );

#endif // ASM_H_INCLUDED
