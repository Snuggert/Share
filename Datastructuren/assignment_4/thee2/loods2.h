/*
 * File: loods2.h
 * 
 * File for defining structs and functions.
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 27-02-2013
 */
#ifndef LOODS
#define LOODS

struct loods2{
	int positionInStack, sizeOfStack;
	char **stack;
};

struct loods2* maakLoods();
int leeg(struct loods2 *storage);
void opslaan(struct loods2 *storage, char *loods);
char* leveren(struct loods2 *storage);
void sloopLoods(struct loods2 *storage);

#endif