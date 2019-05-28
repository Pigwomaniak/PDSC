#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#define MAX_BASE 36
#define NEGATIVE_NUMBER -1
#define INVALID_NUMBER -99
#define MINOR_X -2
#define POSITIVE_NUMBER -3


int decodeValue(char inVal, int base);
long pow5(long x, int y);

long
strtol (const char *nPtr, char **endPtr, int base)
{
    size_t stringSize = strlen(nPtr);
    long finalNumber = 0;
    int valuesOfChars[stringSize];
    //int normalNumbers = 0;
    bool negative = false;
    bool sign = false;
    bool hexa = false;
    int firstWrongNumber = -1;



    if(stringSize == 0){
        return 0;
    }

    if((base < 0) || (base > MAX_BASE)){
        return 0;
    }

    for (int i = 0; i < stringSize; ++i) {
        if(firstWrongNumber == -1) {
            valuesOfChars[i] = decodeValue(nPtr[i], base);
            if (valuesOfChars[i] < 0) {
                if (i == 0) {
                    if (valuesOfChars[i] == NEGATIVE_NUMBER) {
                        negative = true;
                        sign = true;
                    } else if (valuesOfChars[i] == POSITIVE_NUMBER) {
                        negative = false;
                        sign = true;
                    } else if (valuesOfChars[i] == MINOR_X) {
                        if (valuesOfChars[i + 1] == 0) {
                            hexa = true;
                            i++;
                        }
                    } else {
                        firstWrongNumber = i;
                    }
                }
                if (i == 1 && sign) {
                    if (valuesOfChars[i] == MINOR_X) {
                        if (valuesOfChars[i + 1] == 0) {
                            hexa = true;
                            i++;
                        }
                    } else {
                        firstWrongNumber = i;
                    }
                }
            }
            if (firstWrongNumber != -1) {
                *endPtr = (char *)&nPtr[i];
            }
        }
    }
    if(firstWrongNumber == -1){
        firstWrongNumber = stringSize;
        *endPtr = NULL;
    }
    int preNumbers = 0;
    if(hexa){
        preNumbers++;
    }
    if(sign){
        preNumbers++;
    }
    long power = 0;
    for (int j = firstWrongNumber - 1; j >= 0 + preNumbers ; --j) {
        finalNumber += valuesOfChars[j] * pow5(base, power++);
        //printf("%d %ld\n", j, finalNumber);
    }

    if(negative){
        finalNumber = -finalNumber;
    }


    //printf("%ld \n", finalNumber);

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

long pow5(long x, int y){
    long final = 1;
    for(int i = 0; i < y; ++i){
        final = final * x;
    }
    //printf("pow5 y= %d final= %ld ", y, final);
    return final;
}