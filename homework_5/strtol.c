//
// Created by maciek on 28/05/19.
//
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>


long pow5(long x, int y);
long charToLong(char input);


long
strtol (const char *nPtr, char **endPtr, int base){
    errno = 0;

    long output = 0;
    const char *beginNumber = NULL;
    const char *endNumber = NULL;
    const char *startPtr = nPtr;
    bool negative = false;

    while ((*nPtr == ' ') || (*nPtr == '\n') || (*nPtr == '\t')){
        nPtr++;
    }
    if(*nPtr == '-'){
        negative = true;
        nPtr++;
    }
    if(*nPtr == '+'){
        nPtr++;
    }
    int newBase = base;
    if(base == 0){
        newBase = 10;
    }

    if(*nPtr == '0'){
        newBase = 8;
        nPtr++;
        if(*nPtr == 'x'){
            newBase = 16;
            nPtr++;
            if(!((((*nPtr - '0') >= 0) && ((*nPtr - '0') < newBase) && ((*nPtr - '0') < 10)) || (((*nPtr - 'A') >= 0) && (*nPtr - 'A') < base - 10))){
                nPtr--;
                if(endPtr){
                    *endPtr = (char*)nPtr;
                }
                return 0L;
            }
        }
        else
            {
            if(!(((*nPtr - '0') >= 0) && ((*nPtr - '0') < base))){
                nPtr--;
            }
        }
    }
    if(base == 0){
        base = newBase;
    }
    beginNumber = nPtr;
    if(base < 2 || base > 36){
        errno = EINVAL;
        if(endPtr){
            *endPtr = (char*)startPtr;
        }
        return 0L;
    }

    while((((*nPtr - '0') >= 0) && ((*nPtr - '0') < base) && ((*nPtr - '0') < 10)) || (((*nPtr - 'A') >= 0) && (*nPtr - 'A') < base - 10)){
        nPtr++;
    }

    if(endPtr){
        *endPtr = (char*)nPtr;
    }
    endNumber = nPtr;
    nPtr--;
    if(endNumber == beginNumber){
        if(endPtr) {
            *endPtr = (char *)startPtr;
        }
        return 0L;
    }
    while (nPtr >= beginNumber){
        long bPower = pow5(base, (endNumber - nPtr - 1));
        if(bPower > 0){
            if((((LONG_MAX - output) / bPower) < charToLong(*nPtr)) && !negative){ //zmienilem znak nierownosci
                errno = ERANGE;
                if(endPtr){
                    *endPtr = (char*) endNumber;
                }
                return LONG_MAX;
            }
        }
        if((charToLong(*nPtr) > 0) && (bPower > 0)) {
            if (((LONG_MIN  + output) / bPower > -charToLong(*nPtr)) && negative) {  //zmienilem caly zapis
                errno = ERANGE;
                if (endPtr) {
                    *endPtr = (char *) endNumber;
                }
                return LONG_MIN;  //zmienilem na min
            }
        }
        output += charToLong(*nPtr) * pow5(base, (endNumber - nPtr - 1));
        nPtr--;
    }
    if(negative){
        output = -output;
    }
    return output;
}

long pow5(long x, int y) {
    long final = 1;
    for (int i = 0; i < y; ++i) {
        final = final * x;
    }
    return final;
}

long charToLong(char input){
    long output;
    if(((input - '0') >= 0) && ((input - '0') < 10)){
        output = input - '0';
    }
    if(((input - 'A') >= 0) && ((input - 'A') < 27)){
        output = input - 'A' + 10;
    }
    return output;
}