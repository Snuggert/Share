/*
 * File: loods3.h
 * 
 * File for defining structs and functions.
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 27-02-2013
 */
#ifndef LOODS
#define LOODS

struct loods3{
	int positionInStack, sizeOfStack;
	char **stack;
};

struct loods3* maakLoods();
int leeg(struct loods3 *storage);
void opslaan(struct loods3 *storage, char *loods);
char* leveren(struct loods3 *storage);
void sloopLoods(struct loods3 *storage);

#endif