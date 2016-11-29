#include "list.h"






//!--------------------------------------------LIST_ELEM--------------------------------------------







#ifndef NDEBUG
	#define LIST_ELEM_OK(list) if (!list_elem_ok(list)) { list_elem_dump(list); assert(!"list elem is not ok!"); }
#else
	#define LIST_ELEM_OK(list)
#endif

int cpy_to_data(list_elem_t * _this, const data_t * data)
{
	LIST_ELEM_OK(_this);

	return strncpy_s(_this->data, MAX_DATA_SIZE, data, MAX_DATA_SIZE);
}

int list_elem_ctor(list_elem_t * _this, list_elem_t * nxt, list_elem_t * prv, const data_t * data)
{
	assert(_this);
	assert(data);

	_this->next = nxt;
	_this->prev = prv;
	_this->data = (data_t *)calloc(MAX_DATA_SIZE, sizeof(_this->data));
	//! move to data
	cpy_to_data(_this, data);

	return 0;
}

list_elem_t * list_elem_new(list_elem_t * nxt, list_elem_t * prv, const data_t * data, size_t list_elem_size)
{
	list_elem_t * result = (list_elem_t *)calloc(list_elem_size, sizeof(*result));

	list_elem_ctor(result, nxt, prv, data);

	return result;
}

int list_elem_dtor(list_elem_t * _this)
{
	assert(_this);

	_this->next = NULL;
	_this->prev = NULL;

	free(_this->data);
	_this->data = NULL;

	return 0;
}

int list_elem_delete(list_elem_t * _this)
{
	list_elem_dtor(_this);
	free(_this);

	return 0;
}

bool list_elem_ok(const list_elem_t * _this)
{
	return _this != NULL &&
		_this->data != NULL;
}

const char * DUMP_FILE_NAME = "list_dump.gv";
#define DUMP_PRINT(...) fprintf(dump, __VA_ARGS__);
int  list_elem_dump(const list_elem_t * _this, FILE * dump, int num)
{
	assert(_this);

	if (!dump)
	{
		fopen_s(&dump, DUMP_FILE_NAME, "w");
		DUMP_PRINT("graph list{\n");
	}

	data_t * data_prev = _this->prev ? _this->prev->data : "NULL";
	data_t * data_next = _this->next ? _this->next->data : "NULL";
	data_t * data_this = _this ? _this->data : "NULL";

	DUMP_PRINT("%d [label=\"%s;\\n0x%p\" shape=box];\n", num - 1, data_prev, _this->prev);
	DUMP_PRINT("%d [label=\"%s;\\n0x%p\" shape=box];\n", num, data_this, _this);
	DUMP_PRINT("%d [label=\"%s;\\n0x%p\" shape=box];\n", num + 1, data_next, _this->next);

	DUMP_PRINT("%d -- %d\n", num - 1, num);
	DUMP_PRINT("%d -- %d\n", num, num + 1);

	return 0;
}
#undef DUMP_PRINT

list_elem_t * list_elem_before(const list_elem_t * _this)
{
	assert(_this);

	return _this->prev;
}
list_elem_t * list_elem_after(const list_elem_t * _this)
{
	assert(_this);

	return _this->next;
}







//!--------------------------------------------LIST--------------------------------------------








#ifndef NDEBUG
	#define LIST_DUMP(list) list_dump(#list, list);
	#define LIST_OK_ASSERT(list) if (!list_ok(list)) { LIST_DUMP(list); abort(); }
#else
	#define LIST_DUMP(list)
	#define LIST_OK_ASSERT(list)
#endif // NDEBUG

int list_ctor(list_t * _this, const data_t * item)
{
	assert(_this);

	_this->count = 1;

	list_elem_t * init_elem = list_elem_new(NULL, NULL, item, 1);

	_this->head  = init_elem;
	_this->tail  = init_elem;

	return 0;
}

int list_dtor(list_t * _this)
{
	assert(_this);

	for (int i = 0; i < _this->count; i++)
		list_pop_front(_this);

	_this->head  = NULL;
	_this->tail  = NULL;
	_this->count = COUNT_POISON;

	return 0;
}

bool list_ok(const list_t * _this)
{
	return _this != NULL					&&
		   _this->count >= 0;
}

int list_dump(const char * varname, const list_t * _this)
{
	assert(_this);

	FILE * dump = NULL;
	fopen_s(&dump, "list_dump.gv", "w");

	fprintf(dump, "graph list{\n");

	list_elem_t * elem = _this->head;

	fprintf(dump, "list_t[label=\"list_t \\\"%s\\\"\\nhead = 0x%p\\ntail = 0x%p\\ncount = %d\"]\n", 
				  varname, _this->head, _this->tail, _this->count);
	fprintf(dump, "list_t -- 1\n");
	fprintf(dump, "list_t -- %d\n", _this->count);

	for (int i = 0; i < _this->count; i++)
	{
		list_elem_dump(elem, dump, i + 1);
		elem = elem->next;
	}

	fprintf(dump, "}\n");

	fclose(dump);

	return 0;
}

data_t * list_front(const list_t * _this)
{
	LIST_OK_ASSERT(_this);

	return _this->head ? _this->head->data : NULL;
}

data_t * list_back(const list_t * _this)
{
	LIST_OK_ASSERT(_this);

	return _this->tail ? _this->tail->data : NULL;
}

data_t * lis_before_num(const list_t * _this, int num)
{
	LIST_OK_ASSERT(_this);

	return list_find_by_num(_this, num - 1 < 0 ? 0 : num - 1); // -1 for before
}

data_t * list_after_num(const list_t * _this, int num)
{
	LIST_OK_ASSERT(_this);

	return list_find_by_num(_this, num + 1 > _this->count ? _this->count : num + 1); // +1 for after
}

int list_push_front(list_t * _this, const data_t * data)
{
	LIST_OK_ASSERT(_this);

	list_elem_t * new_elem = list_elem_new(NULL, _this->tail, data, 1);
	_this->tail->next      = new_elem;
	_this->tail            = new_elem;
	_this->count++;

	LIST_OK_ASSERT(_this);

	return 0;
}

int list_push_back(list_t * _this, const data_t * data)
{
	LIST_OK_ASSERT(_this);

	list_elem_t * new_elem = list_elem_new(_this->head, NULL, data, 1);
	_this->head->prev      = new_elem;
	_this->head            = new_elem;
	_this->count++;

	LIST_OK_ASSERT(_this);

	return 0;
}

int list_push_before_num(list_t * _this, const data_t * data, int num)
{
	LIST_OK_ASSERT(_this);
	assert(num > 0 && num < _this->count);

	list_elem_t * elem = _this->head;
	for (int i = 0; i < num - 1; i++)
		elem = elem->next;

	list_elem_t * new_elem = list_elem_new(elem->next, elem, data, 1);
	//! TieUp
	elem->next->prev       = new_elem;
	elem->next             = new_elem;
	_this->count++;

	LIST_OK_ASSERT(_this);

	return 0;
}

int list_push_after_num(list_t * _this, const data_t * data, int num)
{
	LIST_OK_ASSERT(_this);
	assert(num >= 0 && num < _this->count - 1);

	list_elem_t * elem = _this->head;
	for (int i = 0; i < num; i++)
		elem = elem->next;

	list_elem_t * new_elem = list_elem_new(elem->next, elem, data, 1);
	elem->next->prev = new_elem;
	elem->next = new_elem;
	_this->count++;

	LIST_OK_ASSERT(_this);

	return 0;
}

int list_pop_front(list_t * _this)
{
	LIST_OK_ASSERT(_this);
	assert(_this->count > 0);

	if (_this->count == 1)
	{
		free(_this->tail);
		_this->head = NULL;
		_this->tail = NULL;

		LIST_OK_ASSERT(_this);

		return 0;
	}

	list_elem_t * del = _this->tail;

	_this->tail->prev->next = NULL;
	_this->tail				= _this->tail->prev;
	_this->count--;

	free(del);

	LIST_OK_ASSERT(_this);

	return 0;
}

int list_pop_back(list_t * _this)
{
	LIST_OK_ASSERT(_this);
	assert(_this->count > 0);

	if (_this->count == 1)
	{
		free(_this->tail);
		_this->head = NULL;
		_this->tail = NULL;

		LIST_OK_ASSERT(_this);

		return 0;
	}

	list_elem_t * del = _this->head;

	_this->head->next->prev = NULL;
	_this->head				= _this->head->next;
	_this->count--;

	free(del);

	LIST_OK_ASSERT(_this);

	return 0;
}

data_t * list_find_by_num(const list_t * _this, int num)
{
	LIST_OK_ASSERT(_this);
	assert(num >= 0 && num < _this->count);

	list_elem_t * elem = _this->head;
	if (!elem)
		return NULL;

	for (int i = 0; i < num; i++)
		elem = elem->next;

	LIST_OK_ASSERT(_this);

	return elem->data;
}

int datacmp(const data_t * data1, const data_t * data2)
{
	return strcmp(data1, data2);
}

int list_find_by_item(const list_t * _this, const data_t * item)
{
	LIST_OK_ASSERT(_this);
	assert(item);

	int count = 0;

	list_elem_t * elem = _this->head;
	if (!elem)
		return NULL;

	while (elem && datacmp(elem->data, item))
	{
		elem = elem->next;
		count++;
	}
	if (count >= _this->count)
		count = -1;

	LIST_OK_ASSERT(_this);

	return count;
}