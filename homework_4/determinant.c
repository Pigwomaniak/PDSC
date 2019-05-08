//
// Created by maciek on 07/05/19.
//

#include "determinant.h"


int main(int argc, char* argv[]){
    if(argc != 2){
        printf("file error \n");
        return 0;
    }
    char* matrixFileName = argv[1];
    printf("\n fileName \n %s \n", matrixFileName);
    Matrix mainMatrix = readMatrixFile(matrixFileName);
    printMatrix(mainMatrix);

    printf("\n");

    double det = 5.0;
    det = determinantCalc(mainMatrix);
    printf("Determinant = %lf \n", det);
    clearMatrix(mainMatrix);

    return 0;
}


