#ifndef ANALYSE_H_INCLUDED
#define ANALYSE_H_INCLUDED

//!============FUNCTIONS===========
int  pass       (const char **, int *, int, Stack_t *);
int  ArrWriter  (int * arr, const char * word, int pc, char * cmd, int * OperCnt, int * MaxOperCnt, bool * CmdDefined, int line, Stack_t *);
bool DefCmd     (int *, int *, const char *, int);
bool DefLbl     (const char *, bool, int, Stack_t *, int, int);
int  CheckArgs  (const char *, const char *, int, Stack_t *);
int  CountStr   (char *, int);
int  DivideStrs (char **, const char *, int, int);

#endif