/*
 * File: loods3.c
 * 
 * This program manages the stacked tea packages in the containers.
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 27-02-2013
 */

#include "loods3.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct loods3* maakLoods()
{
	struct loods3 *storage;
	storage = malloc( sizeof(struct loods3) );
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

int leeg(struct loods3 *storage)
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

void opslaan(struct loods3 *storage, char *newUnit)
{
	char *tempUnit;
	tempUnit = strdup(newUnit);
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
	storage->stack[storage->positionInStack] = tempUnit;
	storage->positionInStack ++;
}

char* leveren(struct loods3 *storage)
{
	storage->positionInStack --;
	if(storage->positionInStack < 0)
	{
		storage->positionInStack ++;
		return NULL;
	}
	return storage->stack[storage->positionInStack];
}

void sloopLoods(struct loods3 *storage)
{
	while(leveren(storage) != NULL);

	free(storage->stack);
	storage->stack = NULL;

	free(storage);
	storage = NULL;
}