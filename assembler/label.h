#ifndef LABEL_H_INCLUDED
#define LABEL_H_INCLUDED

//!=========TYPES======
typedef struct lbl
{
	int ptr;
	int LabelSize;
	char * name;
} Label_t;

//!============FUNCTIONS===========
Label_t * Label_new(size_t, size_t);
int       Label_delete(Label_t *);

#endif LABEL_H_INCLUDED