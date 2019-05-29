//
// Created by maciek on 28/05/19.
//
#include <string.h>
#include <stdbool.h>


int decodeValue(char inVal, int base);
long pow5(long x, int y);


long
strtol (const char *nPtr, char **endPtr, int base){
    errno = 0

    long output;
    const char *tnPtr = nPtr;
    const char *beginNumber = NULL;

    while ((*nptr = ' ') || (*nptr = '\n') || (*nptr = '\t')){
        nptr++;
    }
    if(base == 0){
        base = 10;
        if(*nPtr == 0){
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
        *endPtr = (char*)nPtr;
        return 0L;
    }
    //while()


    return output;
}
