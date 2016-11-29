#pragma once

//======================INCLUDES======================
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=======================TYPES========================
typedef char data_t;
typedef struct _iobuf FILE;

typedef struct list_elem
{
	data_t * data;
	struct list_elem * next;
	struct list_elem * prev;
} list_elem_t;

typedef struct list
{
	int count;
	list_elem_t * head;
	list_elem_t * tail;
} list_t;

//======================CONSTANTS=====================
const int COUNT_POISON = -666;
const int MAX_DATA_SIZE = 1000;

//======================FUNCTIONS=====================


//!--------------------------------------------LIST_ELEM_FUNCTIONS--------------------------------------------


int           list_elem_ctor   (list_elem_t * _this, list_elem_t * nxt, list_elem_t * prv, const data_t * data);
list_elem_t * list_elem_new    (list_elem_t * nxt, list_elem_t * prv, const data_t * data, size_t list_elem_size);
int           list_elem_dtor   (list_elem_t * _this);
int           list_elem_delete (list_elem_t * _this);

bool list_elem_ok   (const list_elem_t * _this);
int  list_elem_dump (const list_elem_t * _this, FILE * dump = NULL, int num = 1);

list_elem_t * list_elem_before (const list_elem_t * _this);
list_elem_t * list_elem_after  (const list_elem_t * _this);


//!-----------------------------------------------LIST_FUNCTIONS-----------------------------------------------


int  list_ctor (list_t * _this, const data_t * item);
int  list_dtor (list_t * _this);

bool list_ok   (const list_t * _this);
int  list_dump (const char * varname, const list_t * _this);

data_t * list_front      (const list_t * _this);
data_t * list_back       (const list_t * _this);
data_t * lis_before_num  (const list_t * _this, int num);
data_t * list_after_num  (const list_t * _this, int num);

int list_push_front      (list_t * _this, const data_t * data);
int list_push_back       (list_t * _this, const data_t * data);
int list_push_before_num (list_t * _this, const data_t * data, int num);
int list_push_after_num  (list_t * _this, const data_t * data, int num);

int list_pop_front (list_t * _this);
int list_pop_back  (list_t * _this);

data_t * list_find_by_num  (const list_t * _this, int num);
int      list_find_by_item (const list_t * _this, const data_t * item);