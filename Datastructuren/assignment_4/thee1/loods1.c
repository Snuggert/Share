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

// Init a loods1 struct.
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

// Check if the position in a struct is zero, if so this means the struct is 
// empty.
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

// Store a new string in the struct. (push to stack.)
void opslaan(struct loods1 *storage, char *newUnit)
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

// Deliver the first string from the top of the stack. (pop from stack.)
char* leveren(struct loods1 *storage)
{
	storage->positionInStack --;
	if(storage->positionInStack < 0)
	{
		storage->positionInStack ++;
		return NULL;
	}
	return storage->stack[storage->positionInStack];
}

// Free up the memory.
void sloopLoods(struct loods1 *storage)
{
	while(leveren(storage) != NULL);

	free(storage->stack);
	storage->stack = NULL;

	free(storage);
	storage = NULL;
}