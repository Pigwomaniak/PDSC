//
// Created by maciek on 28/05/19.
//
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <math.h>


long pow5(long x, int y);



long
strtol (const char *nPtr, char **endPtr, int base){
    errno = 0;

    long output = 0;
    //const char *tnPtr = nPtr;
    const char *beginNumber = NULL;
    const char *endNumber = NULL;
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
    if(base == 0){
        base = 10;
        if(*nPtr == '0'){
            base = 8;
            nPtr++;
            if(*nPtr == 'x'){
                base = 16;
                nPtr++;
            }
        }
    }
    beginNumber = nPtr;
    if(base < 2 || base > 36){
        errno = EINVAL;
        if(endPtr){
            *endPtr = (char*)nPtr;
        }
        return 0L;
    }
    while((((*nPtr - '0') >= 0) && ((*nPtr - '0') < base) && ((*nPtr - '0') < 10)) || (((*nPtr - 'A') >= 0) && (*nPtr - 'A') < base - 10)){
        nPtr++;
    }
    if(endPtr){
        *endPtr = (char*)nPtr;
        endNumber = nPtr;
        nPtr--;
    }
    while (nPtr >= beginNumber){
        long bPower = pow5(base, (endNumber - nPtr - 1));
        if((((LONG_MAX - output) / bPower) > *nPtr) && !negative){
            errno = ERANGE;
            if(endPtr){
                *endPtr = (char*)nPtr;
            }
            return LONG_MAX;
        }
        if(((LONG_MIN /(*nPtr * bPower)) > -output) && negative) {
            errno = ERANGE;
            if (endPtr) {
                *endPtr = (char *) nPtr;
            }
            return LONG_MAX;
        }
        output += *nPtr * (endNumber - nPtr - 1);
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
    //printf("pow5 y= %d final= %ld ", y, final);
    return final;
}