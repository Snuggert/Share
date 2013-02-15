#include "stdlib.h"
#include "stdio.h"
#include "limits.h"
#include "math.h"

int getFreq(char *filename, float *freqArray);
int getEncrypted(char *filename, char **contentArray);
int tryOffsets(float *freqAlphabet, char *fileContent);
int getOffsetFromUser(int min, int max);
int decryptWithOffset(int offset, char *encryptedFile);
void printErrorFaq();