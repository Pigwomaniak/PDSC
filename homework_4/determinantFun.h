//
// Created by maciek on 07/05/19.
//

#ifndef PDSC_DETERMINANTFUN_H
#define PDSC_DETERMINANTFUN_H

#include <stdio.h>
#include <stdlib.h>


#define ERROR (sizeof(int))


FILE *filePointer;

typedef struct Matrix {
    double *matrix;
    unsigned size;
} Matrix;

Matrix readMatrixFile(char *matrixFileName);
Matrix createMatrix(Matrix matrix);
void clearMatrix(Matrix matrix);
void printMatrix(Matrix matrix);
double getMatrix(double *matrix, unsigned size, int line, int column);
double determinantCalc(Matrix tab);

#endif //PDSC_DETERMINANTFUN_H
