/* dummy implementation of strtol */


#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_BASE 36
#define NEGATIVE_NUMBER -1
#define INVALID_NUMBER -99
#define MINOR_X -2


int decodeValue(char inVal, int base);

long
strtol (const char *nPtr, char **endPtr, int base)
{
  size_t stringSize = strlen(nPtr);
  long finalNumber = 0;
  int valuesOfChars[stringSize];
  int normalNumbers = 0;

  if(stringSize == 0){
    return 0;
  }
  /* sprawdzenie poprawności wejść*/
  if((base < 0) || (base > MAX_BASE)){
    return 0;
  }



  /* ocena podstawy systemu liczbowego*/


  /* konwersja */

  /*
  for (int sign = stringSize - 1; sign > 1 ; --sign) {
    int value = decodeValue(nPtr, base);
    if(value > 0){
      finalNumber += value * base;
    }
    if(value == NEGATIVE_NUMBER){
      finalNumber = -finalNumber;
    }
  }
  */
  for (int i = 0; i < stringSize; ++i) {
    valuesOfChars[i] = decodeValue(nPtr[i], base);
    if(valuesOfChars[i] >= 0){
      normalNumbers++;
    }
  }

  int power = 0;
  bool isNegative = false;
  for (int j = 0; j <stringSize ; ++j) {
    if(valuesOfChars[j] > 0){
      long sPow = 1;
      long xPow = base;
      int yPow = normalNumbers - power++ - 1;
      for (int p = 0; p < yPow; ++p) {
        sPow = sPow * xPow;
      }

      finalNumber += valuesOfChars[j] * sPow;
    }
    if(valuesOfChars[j] == NEGATIVE_NUMBER){
      isNegative = true;
    }
  }

  if(normalNumbers == 0){
    return 0;
  }
  if(isNegative){
    finalNumber = -finalNumber;
  }


  return finalNumber;
}

int decodeValue(char inVal, int base){
  int outVal;
  if((inVal >= '0') && (inVal <= '9')){
    if((inVal - '0') < base){
      return inVal - '0';
    }
  }
  if((inVal >= 'A') && (inVal <= 'Z')){
    outVal = inVal - 'A' + 10;
    if(outVal < base){
      return outVal;
    }
  }
  if(inVal == '-'){
    return NEGATIVE_NUMBER;
  }
  if(inVal == 'x'){
    return MINOR_X;
  }
  return INVALID_NUMBER;
}