#include "stdlib.h"
#include "stdio.h"
#include "limits.h"

int getFreq(char *filename, float *freqArray);
int getEncrypted(char *filename, char **contentArray);
int tryOffsets(char *fileContent, float *freqAlphabet);
int getOffsetFromUser(int min, int max);
int decryptWithOffset(int offset, char *encryptedFile);
void printErrorFaq();


// Fill an alphabetic array with frequencies belonging to a language.
int getFreq(char *filename, float *freqArray)
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

// Fill an array with the contents of the encrypted file.
int getEncrypted(char *filename, char **contentArray)
{
	char ch;
	int index, currentArraySize;
	index = 0;
	currentArraySize = 256;
	// Create filepointer to the filename.
	FILE *filePointer = fopen(filename,"r");

	if( filePointer == NULL )
	{
		return 4;
	}

	// while the end of the file is not reached put chars in array.
	while(( ch = fgetc(filePointer) ) != EOF )
	{
 		// ignore every none lowercase character.
 		if((ch - 'a' >= 0 && ch - 'a' < 26) || ch == ' ')
 		{
 			*contentArray[index]= ch;
 			index++;
 		}
 		// if the array size is reached arraysize is increased.
 		if(index == currentArraySize)
 		{
 			char *temp = realloc(contentArray, currentArraySize*2);
 			if ( temp != NULL ) //realloc was successful
			{
			   *contentArray = temp;
			   free(temp);
			}
			else
			{
				return 6;
			}
 			currentArraySize *= 2;
 		}
	}
	fclose(filePointer);

	// fill the remainder of the array with empty chars.
	while(index < currentArraySize)
	{
		contentArray[index] = 0;
		index++;
	}

	return 0;
}

// function to try all offsets 0 to 25 on a file.
int tryOffsets(char *fileContent, float *freqAlphabet)
{
	char ch;
	// Make an array with a place to count charachters a-z
	int alphabet[26], index, numberOfChars, alphabetIndex, offset;
	double percentage, mindifference, difference;
	mindifference = 999;
	index = 0;
	while(1)
	{
		ch = fileContent[index];
		if(ch == 0 || index == 256)
		{
			break;
		}
		index++; 
		printf("%c", ch); 
	}

	printf("\nTrying offsets:\n");

	// try all the offsets 0 to 25
	for(offset = 0; offset < 26; offset++)
	{
		printf(" %d", offset);

		//reset values
		index = 0;
		difference = 0;
		numberOfChars = 0;
		for(index = 0; index < 26; index++)
		{
			alphabet[index] = 0;
		}

		
		// loop through charArray skipping spaces.		 
		while(1)
		{
			ch = fileContent[index];
			// break if NULL is found.
			if(ch == 0)
			{
				break;
			}
			index++;
			if(ch != ' ')
			{
				ch = (((ch -'a') + offset)%26) + 'a';
				alphabetIndex = ch - 'a';
				alphabet[alphabetIndex] ++;
				numberOfChars ++;
			}       
		}

		// for each letters check the difference in frequencies compared to the 
		// frequencyfile
		for(index = 0; index < 26; index++)
		{
			percentage = ((double)alphabet[index]/(double)numberOfChars)*100;
			difference += fabs(percentage - freqAlphabet[index]);
			// printf("%f\n", freqAlphabet[index]);
		}
		// if the difference is smaller let it know to the user.
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
      return 5;
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
	printf("comment section in the top of the code.\n");
}