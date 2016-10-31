#ifndef WRITE_H_INCLUDED
#define WRITE_H_INCLUDED

//!============FUNCTIONS===========
int    CountStr    (char *, int);
int    DivideStrs  (char **, const char *, int, int);
int    LineAnalyse (int *, const char *, int);
int    FirstPass   (const char **, int); //! searching labels
int    LastPass    (int *, const char **, int, FILE *); //! writing to object file
bool   FindLabels  (const char *, char *, int);
int    CountWords  (const char *);

#endif