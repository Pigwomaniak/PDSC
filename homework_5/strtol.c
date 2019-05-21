/* dummy implementation of strtol */


#include <string.h>
#include <bool.h>

#define MAX_BASE 36


int decodeValue(char inVal);

long
strtol (const char *nPtr, char **endPtr, int base)
{
  size_t stringSize = strlen(*nPtr);
  long finalNumber = 0;
  if(stringSize == 0){
    return 0;
  }
  /* sprawdzenie poprawności wejść*/
  if((base < 0) || (base > MAX_BASE)){
    return 0
  }



  /* ocena podstawy systemu liczbowego*/

  base

  /* konwersja */

  for (int sign = stringSize - 1; sign > 1 ; --sign) {
    finalNumber += decodeValue(nPtr[sign]) * base;
  }




  return 0;
}

int decodeValue(char inVal){
  int outVal;

  return outVal;
}