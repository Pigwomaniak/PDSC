//
// Created by maciek on 27/05/19.
//

/* dummy implementation of strtol */


#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_BASE 36
#define NEGATIVE_NUMBER -1
#define INVALID_NUMBER -99
#define MINOR_X -2
#define POSITIVE_NUMBER -3


int decodeValue(char inVal, int base);

long
strtol (const char *nPtr, char **endPtr, int base)
{
    size_t stringSize = strlen(nPtr);
    long finalNumber = 0;
    int valuesOfChars[stringSize];
    int normalNumbers = 0;
    bool negative = false;
    bool hexa = false;
    int firstWrongNumber = -1;

    if(stringSize == 0){
        return 0;
    }
    /* sprawdzenie poprawności wejść*/
    if((base < 0) || (base > MAX_BASE)){
        return 0;
    }

    for (int i = 0; i < stringSize; ++i) {
        if(firstWrongNumber == -1) {
            valuesOfChars[i] = decodeValue(nPtr[i], base);
            if (valuesOfChars[i] < 0) {
                if (i == 0) {
                    if (valuesOfChars[i] == NEGATIVE_NUMBER) {
                        negative = true
                    } else if (valuesOfChars[i] == POSITIVE_NUMBER) {
                        negative = false;
                    } else if (valuesOfChars[i] == MINOR_X) {
                        if (valuesOfChars[i + 1] == 0) {
                            hexa = true;
                            i++
                        }
                    } else {
                        firstWrongNumber = i;
                    }
                }
                if (i == 1) {
                    if (valuesOfChars[i] == MINOR_X) {
                        if (valuesOfChars[i + 1] == 0) {
                            hexa = true;
                            i++
                        }
                    } else {
                        firstWrongNumber = i;
                    }
                } else {
                    firstWrongNumber = i;
                }
            }
            if (firstWrongNumber != -1) {
                **endPtr = &*nPtr[i]
            }
        }
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
    if(inVal == '+'){
        return POSITIVE_NUMBER;
    }
    return INVALID_NUMBER;
}




 /* dummy implementation of strtol */

/*
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

    if((base < 0) || (base > MAX_BASE)){
        return 0;
    }

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



*/
