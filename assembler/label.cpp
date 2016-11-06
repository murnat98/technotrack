#include "include.h"

Label_t * Label_new(size_t ThisSize, size_t NameSize)
{
	Label_t * This = (Label_t *)calloc(ThisSize, sizeof(*This));
	for (int i = 0; i < ThisSize; i++)
	{
		This[i].name = (char *)malloc(NameSize * sizeof(*This->name));
		strcpy(This[i].name, CHAR_POISON);
		This[i].ptr = DATA_POISON;
	}
	This->LabelSize = ThisSize;

	return This;
}

int Label_delete(Label_t * This)
{
	for (int i = 0; i < This->LabelSize; i++)
	{
		free(This[i].name);
		This[i].name = NULL;
		This[i].ptr  = DATA_POISON;
	}
	free(This);
	This = NULL;

	return 0;
}
