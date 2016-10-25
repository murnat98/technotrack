#ifndef ANALYSE_H_INCLUDED
#define ANALYSE_H_INCLUDED

//!============FUNCTIONS===========
int    CountStr    (char *, int);
int    DivideStrs  (char **, const char *, int, int);
int    LineAnalyse (int *, const char *, int);
int    DetCmd      (char **, const char *);
bool   DefCmd      (int *, int *, const char *);

#endif