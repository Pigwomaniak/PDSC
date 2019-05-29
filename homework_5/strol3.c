//
// Created by maciek on 28/05/19.
//
#include <string.h>
#include <stdbool.h>


int decodeValue(char inVal, int base);
long pow5(long x, int y);


long
strtol (const char *nPtr, char **endPtr, int base){
    long output;
    const char *tnPtr = nPtr;
    size_t stringSize = strlen(nPtr);
    long tabOfNumbers[stringSize];

    while (*nptr++){

    }


    return output;
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

long pow5(long x, int y){
    long final = 1;
    for(int i = 0; i < y; ++i){
        final = final * x;
    }
    //printf("pow5 y= %d final= %ld ", y, final);
    return final;
}