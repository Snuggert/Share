/*
 * File: loods1.h
 * 
 * File for defining structs and functions.
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 27-02-2013
 */
#ifndef LOODS
#define LOODS

struct loods1{
	int positionInStack, sizeOfStack;
	char **stack;
};

struct loods1* maakLoods();
int leeg(struct loods1 *storage);
void opslaan(struct loods1 *storage, char *loods);
char* leveren(struct loods1 *storage);
void sloopLoods(struct loods1 *storage);

#endif