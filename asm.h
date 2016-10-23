#ifndef ASM_H_INCLUDED
#define ASM_H_INCLUDED

//!============CONSTANTS===========
const int MAXCMD = 10;

//!============FUNCTIONS===========
char * GetFName    ();
int    ReadAsm     ( char *, char ** );

int    CountStr    ( char *, int );
int    DivideStrs  ( char **, const char *, int, int );
int    LineAnalyse ( const int *, const char * );
int    WriteObj    ( const char *, long );

#endif // ASM_H_INCLUDED
