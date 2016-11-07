#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "cpu.h"

//!============FUNCTIONS============
long ReadProgram (int ** prg);
int  execute     (const int * prg, cpu_t *, long size);

#endif // MAIN_H_INCLUDED