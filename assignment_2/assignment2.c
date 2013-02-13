/*
 * File: assignment1.c
 * 
 * This file contains a program in c to break the caesar style encryption.
 *
 * ERROR MESSAGES:
 * 1 = *******
 * 2 = Frequency file couldn't be opened.
 * 3 = Faulty frequency file.
 * Author: Abe Wiersma (Snuggert)
 * Date: 11-02-2013
 */

#include "assignment2.h"

int main( int argc, char *argv[] )
{
   // check to see if program is called correctly.
   if(argc != 3)
   {
      printf("Wrong program call.\n");
      return 0;
   }

   // array to store the floats used for the frequency in which characters occur
   float freqAlphabet[26];
   char *encryptedFile = argv[1];
   char *freqFile = argv[2];
   // Make an array with a place to count a-z
   int offset, result;

   result = fillFreqArray(freqFile, freqAlphabet);
   if(result != 0)
   {
      printf("ERROR: %d\n", result);
      return 0;
   }
   result = tryOffsets(encryptedFile, freqAlphabet);
   if(result != 0)
   {
      printf("ERROR: %d\n", result);
      return 0;
   }

   offset = getOffsetFromUser(0, 26);
   decryptWithOffset(offset, encryptedFile);
   return 1;
}