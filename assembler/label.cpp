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

	return This;
}

int Label_delete(Label_t * This)
{
	free(This->name);
	free(This);

	return 0;
}
