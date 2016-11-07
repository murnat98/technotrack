#ifndef INCLUDE_H_INCLUDED
#define INCLUDE_H_INCLUDED

//!==============DEFINES============
#define _CRT_SECURE_NO_WARNINGS
//#define NBEGUG
#ifndef NDEBUG
#define PRINTF( ... ) printf ( __VA_ARGS__ );
#else
#define PRINTF
#endif // NDEBUG

//!=============INCLUDES============
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <assert.h>
#include "main.h"
#include "execute.h"
#include "execute.h"
#include "Stack.h"
#include "cpu.h"

//!===========GLOBAL VARS===========
const char EXENAME[FILENAME_MAX] = "a.obj";
const long PROGSTART = 0;
const char DUMPFILENAM[] = "stack.dump";

#endif // INCLUDE_H_INCLUDED