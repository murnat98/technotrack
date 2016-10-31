#ifndef ANALYSE_H_INCLUDED
#define ANALYSE_H_INCLUDED

//!============FUNCTIONS===========
int    CountStr    (char *, int);
int    DivideStrs  (char **, const char *, int, int);
int    CheckOper   (const  char *, const char *, int); //! if CheckOper returns 0, it's normal, if it returns number < 0, it's error, if it is > 0, it's necessary to do something
int    LineAnalyse (int *, const char *, int);
int    DetCmd      (char **, const char *);
bool   DefCmd      (int *, int *, const char *);
int    DeleteSpcs  (const char *);

#endif