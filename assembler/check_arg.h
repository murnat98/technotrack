#ifndef CHECK_ARG_H_INCLUDED
#define CHECK_ARG_H_INCLUDED

//!============FUNCTIONS===========
#define DEFCMD( name, num, oper ) int check_##name ( const char *, int );
#include "cmds.h"
#undef DEFCMD
bool IsNum(const char *);

#endif