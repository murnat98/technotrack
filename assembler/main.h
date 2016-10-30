#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

//!============DEFINES============
#define _CRT_SECURE_NO_WARNINGS
#define ERROR(file, line, ...) {printf ( "In %s in line %d: %s syntax error: ", file, line ); printf ( __VA_ARGS__ ); system ( "pause" ); abort();}

//!============INCLUDES===========
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <io.h>
#include <locale.h>
#include "read.h"
#include "write.h"
#include "analyse.h"

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
int    ReadAsm(char *, char **);
int    WriteObj(const char *, long, const char *);

#endif // MAIN_H_INCLUDED
