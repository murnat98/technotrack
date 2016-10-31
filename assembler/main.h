#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

//!============DEFINES============
//! TODO: remove _CRT_SECURE_NO_WARNINGS
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
#include "read.h"
#include "write.h"
#include "analyse.h"
#include "check_arg.h"

//!============CONSTANTS===========
const int MAXCMD   = 50;
const int MAXOPER  = 50;
const int MAXLABEL = 255;
const int MAXLABELSINTEXT = 1000;

//! TODO: replace into own file
enum cmds
{
	#define DEFCMD( name, num, ... ) cmd_##name = num,
	#include "cmds.h"
	#undef DEFCMD
	cmd_last
};

//!============TYPES===============
//! TODO: replace into file with labels
typedef struct lbl
{
	int ptr;
	int nLabel;
	char * name;
} Label_t;

//!========GLOBAL_VARS=============
//! TODO: to main
extern Label_t * AllLabels;
extern char _FILE_[FILENAME_MAX];

//!============FUNCTIONS===========
//! TODO: to main
int       ReadAsm      (char *, char **);
int       WriteObj     (const char *, long);
Label_t * Label_new    (size_t, size_t);
int       Label_delete (Label_t *);

#endif // MAIN_H_INCLUDED
