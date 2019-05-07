//
// Created by maciek on 07/05/19.
//

#include "determinantFun.h"


Matrix readMatrixFile(char *matrixFileName){
    Matrix matrix;
    if((filePointer = fopen(matrixFileName, "r")) == NULL){
        printf("FILE OPEN ERROR \n");
    } else{
        fscanf(filePointer, "%u", &matrix.size);
        printf("matrix size = %u \n", matrix.size);
        matrix = createMatrix(matrix);
        double temporary;
        for (int i = 0; i < (matrix.size * matrix.size); ++i) {
            fscanf(filePointer, "%lf", &temporary);
            matrix.matrix[i]=temporary;
            //printf("%lf %lf \n", temporary, matrix.matrix[i]);
        }
    }
    fclose(filePointer);
    return matrix;
}

Matrix createMatrix(Matrix matrix){
    if((matrix.matrix = (double*)malloc(matrix.size * sizeof(double))) == NULL){
        printf("MEMORY ALLOCATION ERROR");
        exit(0);
    }
    return matrix;
}

void clearMatrix(Matrix matrix){
    free(matrix.matrix);
}

double getMatrix(double *matrix, unsigned size, int line, int column){
    if(line > size || column > size){
        printf("GETMATRIX ERROR \n");
        return ERROR;
    }
    return (matrix[column + size * line]);
}

void printMatrix(Matrix matrix){
    for (int i = 0; i < matrix.size; ++i) {
        for (int j = 0; j < matrix.size; ++j) {
            printf("%lf\t", getMatrix(matrix.matrix, matrix.size, i, j));
        }
        printf("\n");
    }
}