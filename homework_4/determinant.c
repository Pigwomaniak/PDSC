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
    clearMatrix(mainMatrix);
    printf("\n");


    return 0;
}

