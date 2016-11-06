#ifndef INCLUDE_H_INCLUDED
#define INCLUDE_H_INCLUDED

//!============DEFINES============
#define _CRT_SECURE_NO_WARNINGS
#define NDEBUG
//#define DEBUG
#define ERROR(file, line, ...) {printf ( "assembler.exe: in %s in line %d: syntax error: ", file, line ); printf ( __VA_ARGS__ ); system ( "pause" ); abort();}
#define WARNING(file, line, ...) {printf ( "assembler.exe: in %s in line %d: warning: ", file, line ); printf ( __VA_ARGS__ );}

#ifdef DEBUG
#define PRINTF( ... ) printf ( __VA_ARGS__ );
#else
#define PRINTF
#endif // DEBUG

//!============INCLUDES===========
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <io.h>
#include <locale.h>
#include <ctype.h>
#include "main.h"
#include "Stack.h"
#include "label.h"
#include "read.h"
#include "write.h"
#include "analyse.h"
#include "check_arg.h"

//!============CONSTANTS===========
const int MAXCMD = 50;
const int MAXOPER = 50;
const int MAXLABELSIZE = 255;
const int MAXLABELCOUNT = 1000;
enum cmds
{
#define DEFCMD( name, num, ... ) cmd_##name = num,
#include "cmds.h"
#undef DEFCMD
	cmd_last
};


//!========GLOBAL_VARS=============
extern char _FILE_[FILENAME_MAX];

#endif INCLUDE_H_INCLUDED