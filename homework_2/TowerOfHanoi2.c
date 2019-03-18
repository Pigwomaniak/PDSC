#include "primlib.h"
#include <stdlib.h>

#define NUMBER_OF_DISCS 4
#define NUMBER_OF_PEGS 3

#define HEIGHT_OF_PEG_BASE 5
#define HEIGHT_OF_PEG_STICK 50
#define DISTANCE_BETWEEN_PEGS 5
#define WIDTH_OF_PEG_STICK 6
#define BASE_OF_DISC 10
#define HEIGHT_OF_FLY 70
#define FLYING_SPEED 2


void drawDisc(int x, int y, int blockNumber){
    rect(x-BASE_OF_DISC/2*blockNumber, y, x+BASE_OF_DISC/2*blockNumber, y+HEIGHT_OF_PEG_BASE,GREEN);
}

void drawPeg(int x){
    rect(x-HEIGHT_OF_PEG_STICK/2,HEIGHT_OF_PEG_BASE,x+HEIGHT_OF_PEG_STICK/2,HEIGHT_OF_PEG_STICK,YELLOW);
}

int positionOfPeg(int peg){
    int x = peg*screenWidth()/NUMBER_OF_PEGS+DISTANCE_BETWEEN_PEGS;
    return x;
}

int positionOfDisc(int stockPosition) {
    int y = (stockPosition + 1) * HEIGHT_OF_PEG_BASE;
    return y;
}

void drawBasicView(){
    filledRect(0, 0, screenWidth(), screenHeight(), BLACK);
    rect(0,0,screenWidth(),HEIGHT_OF_PEG_BASE,GREEN);
    for (int peg = 0; peg < NUMBER_OF_PEGS; ++peg) {
        drawPeg(positionOfPeg(peg));
    }

}

int initialMatrix(int *initialMatrix){
    for (int disc = 0; disc < NUMBER_OF_DISCS; ++disc) {
        initialMatrix[0][disc]=NUMBER_OF_DISCS-disc;
    }
    for (int peg = 1; peg < NUMBER_OF_PEGS; ++peg) {
        for (int disc = 0; disc < NUMBER_OF_DISCS; ++disc) {
            initialMatrix[peg][disc]=0;
        }
    }
    return 0;
}

void drawStaticDiscs(int *matrixOfPegs){
    for (int peg = 0; peg < NUMBER_OF_PEGS; ++peg) {
        for (int disc = 0; disc < NUMBER_OF_DISCS; ++disc) {
            if(matrixOfPegs[peg][disc]!=0){
                drawDisc(positionOfDisc(disc),positionOfPeg(peg),matrixOfPegs[peg][disc]);
            }
        }
    }
}
int moveDirection(int startPeg, int endPeg){
    if (startPeg-endPeg < 0){
        return 1;
    } else{
        return -1;
    }
}

int moveDiscAnimation(int startPeg, int startPos, int endPeg, int endPos, int blockNumber){
    int posX = positionOfPeg(startPeg);
    int posY = positionOfDisc(startPos);
    while (posY != HEIGHT_OF_FLY){
        posY++;
    }
    while (posX!=positionOfPeg(endPeg)){
        posX += moveDirection(startPeg,endPeg);
    }
    while (posY != positionOfDisc(endPos)){
        posY--;
    }
}

int keyDecode(char key){
    int keyOut;
    switch (key){
        case SDLK_1:
            keyOut=1;
            break;
        case SDLK_2:
            keyOut=2;
            break;
        case SDLK_3:
            keyOut=3;
            break;
        case SDLK_4:
            keyOut=4;
            break;
        case SDLK_5:
            keyOut=5;
            break;
        case SDLK_6:
            keyOut=6;
            break;
        case SDLK_7:
            keyOut=7;
            break;
        case SDLK_8:
            keyOut=8;
            break;
        case SDLK_9:
            keyOut=9;
            break;
        default:
            keyOut=0;
            break;
        }
    return keyOut;
}

int getPositionOfFirstDisc(int peg, int *matrixOfPegs){
    int disc=NUMBER_OF_DISCS;
    while (matrixOfPegs[peg][disc] == 0){
        disc--;
    }
    return disc;
}

int checkActionCorrect(int keyPress1, int keyPress2, int *matrixOfPegs){
    int firstDiscNumber = matrixOfPegs[keyPress1][getPositionOfFirstDisc(keyPress1, matrixOfPegs)];
    int secondDiscNumber = matrixOfPegs[keyPress2][getPositionOfFirstDisc(keyPress2, matrixOfPegs)];
    if(firstDiscNumber < secondDiscNumber){
        return 1;
    } else{
        return 0;
    }
}

int executeMove(int pegFrom, int pegOn, int *matrixOfPegs){
    int movingDiscPosition = getPositionOfFirstDisc(pegFrom, matrixOfPegs);
    matrixOfPegs[pegFrom][movingDiscPosition] = 0;
    return 0;
}

int main(){
    int matrixOfPegs[NUMBER_OF_PEGS][NUMBER_OF_PEGS];
    initGraph();
    initialMatrix(matrixOfPegs);
    while(!isKeyDown(SDLK_ESCAPE)){
        int keyPress1 = keyDecode(getkey());
        int keyPress2 = keyDecode(getkey());
        if(checkActionCorrect(keyPress1, keyPress2, matrixOfPegs)){

        }
    }
    return 0;
}

