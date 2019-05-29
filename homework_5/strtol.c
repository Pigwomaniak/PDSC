/* dummy implementation of strtol */


#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

#define MAX_BASE 36
#define NEGATIVE_NUMBER -1
#define INVALID_NUMBER -99
#define MINOR_X -2
#define ADD_SIGN -3
#define BLANK -4


int decodeValue(char inVal, int base);
long pow5(long x, int y);



long
strtol (const char *nPtr, char **endPtr, int base)
{
    errno = 0;
    size_t stringSize = strlen(nPtr);
    long finalNumber = 0;
    int valuesOfChars[stringSize];
    int normalNumbers = 0;
    int startNumberPosition = 0;
    bool isNegative = false;
    bool noBase = false;

    if(stringSize == 0){
        return 0;
    }

    if((base < 0) || (base > MAX_BASE) || (base == 1)){
        errno = EINVAL;
        if(endPtr){
            *endPtr = (char*) nPtr;
        }
        return 0L;
    }
    if(base == 0){
        base = 10;
        noBase = true;
    }
    bool sign = false;
    for (int i = 0; i < stringSize; ++i) {
        valuesOfChars[i] = decodeValue(nPtr[i], base);
        if (valuesOfChars[i] == ADD_SIGN && startNumberPosition == i){
            startNumberPosition++;
            sign = true;
        } else if(valuesOfChars[i] == NEGATIVE_NUMBER && startNumberPosition == i) {
            isNegative = true;
            startNumberPosition++;
            sign = true;
        } else if (valuesOfChars[i] == BLANK && startNumberPosition == i && !sign){
            startNumberPosition++;
        } else if(valuesOfChars[i] >= 0){
            normalNumbers++;
            if(noBase && startNumberPosition == i && valuesOfChars[startNumberPosition + 1] == MINOR_X && valuesOfChars[startNumberPosition] == 0 && stringSize > startNumberPosition + 2){
                startNumberPosition += 2;
                normalNumbers--;
            }
        }

    }
    int endNumberPosition = startNumberPosition;
    while (endNumberPosition < stringSize && valuesOfChars[endNumberPosition] >= 0){
        endNumberPosition++;
    }

    printf(" %d %d %d ",startNumberPosition,endNumberPosition, stringSize);

    int power = 0;


    for (int j = stringSize - 1; j >= startNumberPosition ; --j) {
        if(valuesOfChars[j] >= 0){
            long sPow = 1;
            long xPow = base;
            int yPow = power++;
            /*
            for (int p = 0; p < yPow; ++p) {
                sPow = sPow * xPow;
            }
            */

            sPow = pow5(xPow, yPow);
            if((((LONG_MAX - finalNumber) / sPow) < valuesOfChars[j]) && (!isNegative)){
                errno = ERANGE;
                if(endPtr){
                    *endPtr = (char*)(nPtr + endNumberPosition);
                }
                return LONG_MAX;
            }
            if((((LONG_MIN + finalNumber) / sPow) > -valuesOfChars[j]) && (isNegative)){
                errno = ERANGE;
                if(endPtr){
                    *endPtr = (char*)(nPtr + endNumberPosition);
                }
                return LONG_MIN;
            }

            finalNumber += valuesOfChars[j] * sPow;
        }
    }

    if(normalNumbers == 0){
        return 0L;
    }
    if(isNegative){
        finalNumber = -finalNumber;
    }


    if(endPtr)
    *endPtr = (char*)(nPtr + (int)endNumberPosition);

    return finalNumber;
}

int decodeValue(char inVal, int base){
    int outVal;
    //printf("%d ",(int)inVal);
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
    if((inVal == '+'))
        return ADD_SIGN;
    if((inVal == ' ') || (inVal ==  '\t') || (inVal ==  '\n')){
        return BLANK;
    }
    return INVALID_NUMBER;
}

long pow5(long x, int y){
    long final = 1;
    for(int i = 0; i < y; ++i){
        final = final * (long)x;
    }
    //printf("pow5 y= %d final= %ld ", y, final);
    return final;
}
