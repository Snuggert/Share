#include "stdlib.h"
#include "stdio.h"

int getOffsetFromUser(int min, int max);
int decryptWithOffset(int offset, char *encryptedFile);
int fillFreqArray(char *filename, float *freqArray);
int tryOffsets(char *encryptedFile, float *freqAlphabet);
void printErrorFaq();


// Fill an alphabetic array with frequencies belonging to a language.
int fillFreqArray(char *filename, float *freqArray)
{
	// Create filepointer to the language frequency file
	FILE *filePointer = fopen(filename,"r");
	if( filePointer == NULL )
	{
		return 2;
	}
	char ch;
	int alphabetIndex, line, floatIndex;
	char tempFloat[10];

	for(line = 0; line < 26; line++) 
	{
		// Put frequency in correct row of table and check if the file is 
		// corrupt.
		alphabetIndex = getc(filePointer) - 'a';
		if(alphabetIndex < 0 || alphabetIndex > 25)
		{
			return 3;
		}
		// Skip the space
		getc(filePointer);

		// The float follows.
		for(floatIndex = 0; floatIndex < 10; floatIndex++) 
		{
			ch = getc(filePointer);
			if (ch == '\n')
			{
				break;
			} 
			tempFloat[floatIndex] = ch;
		}
		tempFloat[floatIndex] = '\0';

		freqArray[alphabetIndex] = strtof(tempFloat, NULL);
	}
	fclose(filePointer);
	return 0;
}

// function to try all offsets 0 to 25 on a file.
// i chose to not put the contents of the file in an array to spare memory space
// usage, even though for the small files we use now it takes some time more
// for every loop.
int tryOffsets(char *encryptedFile, float *freqAlphabet)
{
	char ch;
	int alphabet[26], index, numberOfChars, alphabetIndex, offset;
	double percentage, mindifference, difference;
	FILE *filePointer;
	mindifference = 999;
	printf("\nTrying offsets:\n");
	// try all the offsets 0 to 25
	for(offset = 0; offset < 26; offset++)
	{
		printf(" %d", offset);
		// Create filepointer to the encrypted file.
		filePointer = fopen(encryptedFile,"r");

		//reset values
		numberOfChars = 0;
		difference = 0;
		for(index = 0; index < 26; index++)
		{
			alphabet[index] = 0;
		}

		//check filepointer for validity
		if( filePointer == NULL )
		{
			printf("Error while opening the file.\n");
			return 0;
		}

		/*
		* loop through file character by character every non space character 
		* gets counted and the number of occurences of a character is kept.
		*/
		while( ( ch = fgetc(filePointer) ) != EOF )
		{
			if(ch != ' ')
			{
				ch = (((ch -'a') + offset)%26) + 'a';
				numberOfChars ++;
				alphabetIndex = ch;
				alphabetIndex -= 'a';
				if(alphabetIndex < 0 || alphabetIndex > 25)
				{
					printf("Wrong file format in encrypted file.\n");
					return 0;
				}
				alphabet[alphabetIndex] ++;
			}        
		}
		fclose(filePointer);
		for(index = 0; index < 26; index++)
		{
			percentage = ((double)alphabet[index]/(double)numberOfChars)*100;
			difference += fabs(percentage - freqAlphabet[index]);
		}
		if(difference < mindifference)
		{
			printf("*");
			mindifference = difference;
		}
	}
	return 0;
}

// get offset from user.
int getOffsetFromUser(int min, int max)
{
	printf("\nDecoding with offset: ");
	int input;   
	input = 0;

	while (scanf("%d",&input) != 1 || input < min || input > max)
	{
		printf("Wrong input: ");
	}
	return input;
	return 0;
}

// function to print a file with a offset.
int decryptWithOffset(int offset, char *encryptedFile)
{
   char ch;
   FILE *filePointer;

   // Create filepointer to the encrypted file.
   filePointer = fopen(encryptedFile,"r");

   //check filepointer for validity
   if( filePointer == NULL )
   {
      printf("Error while opening the file.\n");
      return 0;
   }

   printf("\n");
   // loop through the file and print every char.
   while( ( ch = fgetc(filePointer) ) != EOF )
   {
      // if a char is not a space it will be set off by the offset given.
      if(ch != ' ')
      {
         ch = (((ch -'a') + offset)%26) + 'a';
      }
      printf("%c", ch);
   }
   fclose(filePointer);
   return 0;
}
// function to print ref to where the actual meaning of error messages is located.
void printErrorFaq()
{
	printf("Please refer to the documentation in the");
	printf("comment section above the code.\n");
}