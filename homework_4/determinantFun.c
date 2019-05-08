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
    if((matrix.matrix = (double*)malloc(matrix.size * matrix.size * sizeof(double))) == NULL){ // sprawdzić czy odpowiednia ilość jest
        printf("MEMORY ALLOCATION ERROR \n");
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

double determinantCalc(Matrix tab){
    //printMatrix(tab);
    //printf("\n");
    double det = 0.0;
    if(tab.size == 1){
        det = tab.matrix[0];
        //printf("pojedynczy determinant = %lf\n", tab.matrix[0]);
    } else{
        for (int column = 0; column < tab.size; ++column) {
            Matrix smallTab = createSmallTab(tab, column);
            det += determinantCalc(smallTab) * pow((-1), (1 + column + 1)) * getMatrix(tab.matrix, tab.size, 0, column);
            clearMatrix(smallTab);
        }
    }
    //printf("kolejne determinanty = %lf\n", det);
    //printMatrix(tab);
    //printf("\n");
    return det;
}

Matrix createSmallTab(Matrix bigTab, int columnToDelete){

    Matrix smallTab;
    smallTab.size = bigTab.size - 1;
    smallTab = createMatrix(smallTab);
    //printf("creating smal tab size = %u\n", smallTab.size);
    int dataNumber = 0;
    for (int line = 1; line < bigTab.size; ++line) {
        for (int column = 0; column < bigTab.size; ++column) {
            if(column != columnToDelete) {
                smallTab.matrix[dataNumber++] = getMatrix(bigTab.matrix, bigTab.size, line, column);
            }
        }
    }

    return smallTab;
}
