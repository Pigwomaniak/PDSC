//
// Created by maciek on 08/03/19.
//
#include "primlib.h"
#include <stdlib.h>

#define NUBER_OF_DISCS 4
#define NUMBER_OF_PEGS 3

#define HEIGH_OF_PEG_BASE 5
#define HEIGH_OF_PEG_STICK 50
#define DISTANCE_BEETWEN_PEGS 5
#define WIDTH_OF_PEG_STICK 6
#define BASE_OF_DISC 10


typedef struct Block{
    int sizeOfBlock;
    int positionOnPeg;
    int pegNumber;
    bool isInMove;
    bool isBlock;
};

void drawPeg(int currentPegNumber){
    int pegScale=screenHeight()/NUMBER_OF_PEGS;
    rect(currentPegNumber*pegScale+DISTANCE_BEETWEN_PEGS,0,(currentPegNumber+1)*pegScale-DISTANCE_BEETWEN_PEGS,HEIGH_OF_PEG_BASE);
    rect(currentPegNumber*pegScale/2-WIDTH_OF_PEG_STICK,HEIGH_OF_PEG_BASE,currentPegNumber*pegScale/2+WIDTH_OF_PEG_STICK,HEIGH_OF_PEG_STICK);
}

void drawBackground(){
    filledRect(0, 0, screenWidth() - 1, screenHeight() - 1, BLACK);
    for(currentPegNumber = 0; currentPegNumber < NUMBER_OF_PEGS; currentPegNumber++)
    {
        drawPeg(currentPegNumber);
    }
}

Block makeStartMatrix(Block startMatrixOfBlocks[][], int discQuantity, int pegsQuantity
){
    for(int disc=0; disc < discQuantity; disc++)
    {
        startMatrixOfBlocks[disc][0].isInMove=0;
        startMatrixOfBlocks[disc][0].pegNumber=0;
        startMatrixOfBlocks[disc][0].positionOnPeg=disc;
        startMatrixOfBlocks[disc][0].sizeOfBlock=NUBER_OF_DISCS-disc;
        startMatrixOfBlocks[disc][0].isBlock=1;
    }
    for(int peg = 1; peg < pegsQuantity; peg++)
    {
        for (int disc = 0; disc < discQuantity; ++disc)
        {
            startMatrixOfBlocks[disc][peg].isBlock=0;
        }
    }
    return startMatrixOfBlocks[][];
}

void drawDisc(int x, int y, int blockNumber){
    rect(x-BASE_OF_DISC/2*blockNumber, y, x+BASE_OF_DISC/2*blockNumber, y+HEIGH_OF_PEG_BASE);
}

int positionOfPeg(int peg, int pegsQuantity){
    int x=peg*screenWidth()/NUMBER_OF_PEGS+DISTANCE_BEETWEN_PEGS;
    return x;
}

int positionOfDisc(int stockPosition) {
    int y = (stockPosition + 1) * HEIGH_OF_PEG_BASE;
    return y;
}

void drawStaticDiscs(Block matrixOfBlocks[][],int pegsQuantity, int discQuantity){
    for (int peg = 0; peg < pegsQuantity; ++peg)
    {
        for (int disc = 0; disc < discQuantity; ++disc) {
            if(matrixOfBlocks[disc][peg].isBlock){
                drawDisc(positionOfPeg(peg,pegsQuantity),positionOfDisc(disc),disc);
            }
        }
    }
}

int main()
{
    Block matrixOfBlocks[NUBER_OF_DISCS][NUMBER_OF_PEGS];


    return 0;
}

