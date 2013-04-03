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
	unsigned long long index, randomNumbersInside;
	unsigned long long randomNumbers;
	long double fourthPI, myPI;

	if(argc > 0)
	{
		if(atoi( (argv[1]) ) >= 0)
		{
			randomNumbers = atoi( (argv[1]) );
			randomNumbersInside = 0;

			printf("\nNumbers to be generated: %llu \n", randomNumbers);

			/*
			 * A random number is chosen the number of times the user defines.
			 * If the random number is located within a radius of 1/4th of a
			 * circle, randomNumbersInside is incremented.
			 */
			for (index=0; index<randomNumbers; index++) {
				long double x, y, lengthxy;
				x = getRandom();
				y = getRandom();
				lengthxy = sqrt(pow(x, 2.0)+ pow(y, 2.0));
				if(lengthxy <= 1.0){
					randomNumbersInside ++;
				}
			}
			/*
			 * Ratio of numbers inside and numbers outside is calculated and the
			 * ratio is multiplied by four to get the approxamation of PI.
			 */
			fourthPI = (long double)randomNumbersInside / 
				(long double)randomNumbers;
			myPI = fourthPI * 4.0;

			printf("Numbers inside: %llu \n", randomNumbersInside);

			printf("\nVery inaccurate PI: %Lf \n", myPI);
		}
		else
		{
			printf("\nERROR:Number given below zero\n");
		}
	}
	else
	{
		printf("\nERROR:No number given\n");
	}

	printf("\nWaiting for enter to exit:");
	getchar();
	return 0;
}

/*
 * function to get random number between 0 and 1
 */
long double getRandom ()
{
	return (long double)rand() / (long double)RAND_MAX;
}