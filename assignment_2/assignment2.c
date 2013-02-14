/*
 * File: assignment1.c
 * 
 * This file contains a program in c to break the caesar style encryption.
 *
 * ERROR MESSAGES:
 * 1 = Wrong program call.
 * 2 = Frequency file couldn't be opened.
 * 3 = Faulty frequency file.
 * 4 = Error opening file while trying offsets
 * 5 = Error opening file while decrypting file with user offset.
 * 6 = Memory allocation error.
 * Author: Abe Wiersma (Snuggert)
 * Date: 11-02-2013
 */

#include "assignment2.h"

int main( int argc, char *argv[] )
{
   // check to see if program is called correctly.
   if(argc != 3)
   {
      printf("ERROR 1\n");
      return 0;
   }

   // array to store the floats used for the frequency in which characters occur
   char *encryptedFile = argv[1];
   char *freqFile = argv[2];
   float *freqAlphabet;
   freqAlphabet = malloc(26*sizeof(float));
   char *encryptedFileContent;
   encryptedFileContent = malloc(256);
   int offset, result;

   result = getFreq(freqFile, freqAlphabet);
   if(result != 0)
   {
      printf("ERROR: %d\n", result);
      printErrorFaq();
      return 0;
   }

   result = getEncrypted(encryptedFile, *encryptedFileContent);
   if(result != 0)
   {
      printf("ERROR: %d\n", result);
      printErrorFaq();
      return 0;
   }

   for(int index = 0; index < 26; index++)
   {
      printf("%f\n", freqAlphabet[index]);
   }

   result = tryOffsets(freqAlphabet, encryptedFileContent);
   if(result != 0)
   {
      printf("ERROR: %d\n", result);
      printErrorFaq();
      return 0;
   }

   offset = getOffsetFromUser(0, 26);

   result = decryptWithOffset(offset, encryptedFileContent);
   if(result != 0)
   {
      printf("ERROR: %d\n", result);
      printErrorFaq();
      return 0;
   }

   return 0;
}