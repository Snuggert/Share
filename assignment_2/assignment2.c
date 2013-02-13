/*
 * File: assignment1.c
 * 
 * This file contains a program in c to break the caesar style encryption.
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 11-02-2013
 */

#include <stdlib.h>
#include <stdio.h>

int getOffset(int min, int max);
void printOffset(int offset, char *encryptedFile);

int main( int argc, char *argv[] )
{
   if(argc == 3)
   {
      char ch;
      char freqAlphabet[26][10];
      char *encryptedFile = argv[1];
      char *freqFile = argv[2];
      // Make an array with a place to count a-z
      int alphabet[26], index, freqIndex, numberOfChars, secondIndex, 
         alphabetIndex, floatFlag, offset;
      double percentage, mindifference, difference;
      FILE *filePointer;

      floatFlag = 0;
      freqIndex = 0;
      index = 0;
      mindifference = 999;

      // Empty the array
      for(index = 0; index < 26; index++)
      {
         for(secondIndex = 0; secondIndex < 10; secondIndex++)
         {
            freqAlphabet[index][secondIndex] = 0;
         }
      }

      // Create filepointer to the language frequency file
      filePointer = fopen(freqFile,"r");

      //check filepointer for validity
      if( filePointer == NULL )
      {
         perror("Error while opening the file.\n");
         exit(EXIT_FAILURE);
      }

      // load the frequency file into the freqAlphabet array.
      while( ( ch = fgetc(filePointer) ) != EOF )
      {
         if(ch == ' ')
         {
            floatFlag = 1;
            index = 0;
         }
         else if(ch == '\n')
         {
            floatFlag = 0;
         }
         else if(floatFlag == 0)
         {
            freqIndex = ch - 'a';
            if(freqIndex < 0 || freqIndex > 25)
            {
               perror("Wrong file format in language frequency file.\n");
               exit(EXIT_FAILURE);
            }
         }
         else
         {
            freqAlphabet[freqIndex][index] = ch;
            index ++;
         }
      }
      fclose(filePointer);

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
            perror("Error while opening the file.\n");
            exit(EXIT_FAILURE);
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
                  perror("Wrong file format in encrypted file.\n");
                  exit(EXIT_FAILURE);
               }
               alphabet[alphabetIndex] ++;
            }        
         }
         fclose(filePointer);
         for(index = 0; index < 26; index++)
         {
            percentage = ((double)alphabet[index]/(double)numberOfChars)*100;
            difference += fabs(percentage - atof(freqAlphabet[index])); 
         }
         if(difference < mindifference)
         {
            printf("*");
            mindifference = difference;
         }
      }

      printf("\nDecoding with offset: ");
      offset = getOffset(0, 26);
      printOffset(offset, encryptedFile);
      return 0;
   }
   else
   {
      printf("\nIncorrect way of calling the program.\n");
      return 0;
   }
}

// get offset from user.
int getOffset(int min, int max)
{
   int input;   
   input = 0;

   while (scanf("%d",&input) != 1 || input < min || input > max)
   {
      printf("Wrong input: ");
   }
   return input;
}

// function to print a file with a offset.
void printOffset(int offset, char *encryptedFile)
{
   char ch;
   FILE *filePointer;

   // Create filepointer to the encrypted file.
   filePointer = fopen(encryptedFile,"r");

   //check filepointer for validity
   if( filePointer == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
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
}