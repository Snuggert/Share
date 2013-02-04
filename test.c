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
	int r, index, randomNumbersInside;
	long randomNumbers;
	long double fourthPI, myPI;

	randomNumbers = atoi( (argv[1]) );
	randomNumbersInside = 0;
	r = 1;
	printf("To be generated: %d \nwidth/height/radius: %d\n", randomNumbers, r);

	for (index=0; index<randomNumbers; index++) {
		long double x, y, lengthxy;
		x = getRandom();
		y = getRandom();
		lengthxy = sqrt(pow(x, 2.0)+ pow(y, 2.0));
		if(lengthxy <= 1.0){
			randomNumbersInside ++;
		}
	}
	printf("Numbers inside: %d \n", randomNumbersInside);
	fourthPI = (long double)randomNumbersInside / (long double)randomNumbers;
	myPI = fourthPI * 4.0;
	printf("Very inaccurate PI %Lf \n", myPI);
	printf("Waiting for enter to exit: \n");
	getchar();

	return 0;

}

long double getRandom ()
{
	return (long double)rand() / (long double)RAND_MAX;
}