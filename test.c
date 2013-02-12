/*
 * File: assignment1.c
 * 
 * This file contains a very inaccurate way to calculate PI
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 04-02-2013
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

long double getRandom();

int main( int argc, char *argv[] )
{
	char a = 'a';
	printf("%c\n", ((a-'a' + 2)%26) + 'a');
}