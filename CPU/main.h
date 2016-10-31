#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

//!==============DEFINES============
#define _CRT_SECURE_NO_WARNINGS
//#define NBEGUG
#ifndef NDEBUG
	#define PRINTF( ... ) printf ( __VA_ARGS__ );
#else
	#define PRINTF
#endif // DEBU

//!=============INCLUDES============
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <assert.h>
#include "execute.h"
#include "execute.h"
#include "Stack.h"
#include "cpu.h"


//! TODO: from this moment -> to .cpp
//!============FUNCTIONS============
int execute();

//!===========GLOBAL VARS===========
const char EXENAME[FILENAME_MAX] = "a.obj";
const long PROGSTART = 0;

#endif // MAIN_H_INCLUDED
