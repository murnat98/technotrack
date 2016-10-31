#include "main.h"

Label_t * Label_new(size_t ThisSize, size_t NameSize)
{
	Label_t * This = (Label_t *)calloc(ThisSize, sizeof(*This));
	This->name = (char *)calloc(NameSize, sizeof(*This->name));
	This->ptr = 0;
	This->nLabel = 0;

	return This;
}

int Label_delete(Label_t * This)
{
	free(This->name);
	free(This);

	return 0;
}