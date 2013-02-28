/*
 * File: loods1.c
 * 
 * This program manages the stacked tea packages in the containers.
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 27-02-2013
 */

#include "loods1.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct loods1* maakLoods()
{
	struct loods1 *storage;
	storage = malloc( sizeof(struct loods1) );
	if(storage == NULL)
	{
		return NULL;
	}
	storage->sizeOfStack = 16;
	storage->positionInStack = 0;

	storage->stack = calloc(storage->sizeOfStack, sizeof(char *) );
	if(storage->stack == NULL)
	{
		return NULL;
	}

	return storage;
}

int leeg(struct loods1 *storage)
{
	if(storage->positionInStack == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void opslaan(struct loods1 *storage, char *newUnit)
{
	if (storage->positionInStack == storage->sizeOfStack) 
	{
		storage->sizeOfStack *= 2;
		storage->stack = realloc(storage->stack,
			storage->sizeOfStack * sizeof(char *));
		if (storage->stack == NULL)
		{
			perror("Reallocation of stack failed.");
			exit(EXIT_FAILURE);
		}
	}
	printf("anus\n");
	strcpy(storage->stack[storage->positionInStack], newUnit);
	printf("%d\n", storage->positionInStack);
	storage->positionInStack ++;
}

char* leveren(struct loods1 *storage)
{
	storage->positionInStack --;
	if(storage->positionInStack < 0)
	{
		storage->positionInStack ++;
		return NULL;
	}
	printf("%d\n", storage->positionInStack);
	return storage->stack[storage->positionInStack];
}

void sloopLoods(struct loods1 *storage)
{
	while(leveren(storage) != NULL)

	free(storage->stack);
	storage->stack = NULL;

	free(storage);
	storage = NULL;
}