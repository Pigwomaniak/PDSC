#include "primlib.h"
#include <stdlib.h>
#include <assert.h>

#define NUMBER_OF_DISCS 8
#define NUMBER_OF_PEGS 6
#define HEIGHT_OF_PEG_BASE 0.05
#define HEIGHT_OF_PEG_STICK 0.6
#define WIDTH_OF_PEG_STICK 0.005
#define BASE_OF_DISC 0.04
#define HEIGHT_OF_FLY 0.7
#define REFRESH_TIME_IN_MS 2

static int top[NUMBER_OF_PEGS];             /* first empty slot on the stack */
static int size = NUMBER_OF_DISCS;
static int matrixOfPegs[NUMBER_OF_PEGS][NUMBER_OF_DISCS];

void push(int discNumber, int peg){
    assert(top[peg] < size);
    matrixOfPegs[peg][top[peg]++]=discNumber;
}

int pop(int peg){
    assert(top[peg] > 0);
    return matrixOfPegs[peg][--top[peg]];
}

int peak(int peg){
    assert(top[peg] > 0);
    return matrixOfPegs[peg][top[peg]-1];
}

int getHeightPegBase(){
    return (screenHeight()*HEIGHT_OF_PEG_BASE);
}

int getHeightPegStick(){
    return (screenHeight()*HEIGHT_OF_PEG_STICK);
}

int getWidthPegStick(){
    return (screenWidth()*WIDTH_OF_PEG_STICK);
}

int getBaseDisc(){
    return ((screenWidth()/(NUMBER_OF_PEGS))/(NUMBER_OF_DISCS*2));
}

void drawDisc(int x, int y, int blockNumber){
    filledRect(x - getBaseDisc()/2*blockNumber, y, x + getBaseDisc()/2*blockNumber, y + getHeightPegBase(),BLUE);
}

void drawPeg(int x){
    filledRect(x-getWidthPegStick()/2, screenHeight() - getHeightPegBase(),x+getWidthPegStick()/2, screenHeight() - getHeightPegStick(),YELLOW);
}

int positionOfPeg(int peg){
    return ((peg+1)*screenWidth()/(NUMBER_OF_PEGS+1));
}

int positionOfDisc(int stockPosition) {
    int y = screenHeight() - (stockPosition + 2) * getHeightPegBase();
    return y;
}

void drawBasicView(){
    filledRect(0, 0, screenWidth(), screenHeight(), BLACK);
    filledRect(0,screenHeight(),screenWidth(), screenHeight() - getHeightPegBase(),GREEN);
    for (int peg = 0; peg < NUMBER_OF_PEGS; ++peg) {
        drawPeg(positionOfPeg(peg));
    }
}

int initialMatrix(){
    for (int peg = 0; peg < NUMBER_OF_PEGS; ++peg) {
        top[peg]=0;
    }
    for (int disc = NUMBER_OF_DISCS; disc > 0; disc--) {
        push(disc, 0);
    }
    return 0;
}

void drawStaticDiscs(){
    for (int peg = 0; peg < NUMBER_OF_PEGS; ++peg) {
        for (int disc = 0; disc < top[peg]; ++disc) {
            drawDisc(positionOfPeg(peg),positionOfDisc(disc),matrixOfPegs[peg][disc]);
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

void updateAnimation(int discPosX, int discPosY, int discNumber){
    drawBasicView();
    drawStaticDiscs();
    drawDisc(discPosX, discPosY, discNumber);
    updateScreen();
    SDL_Delay(REFRESH_TIME_IN_MS);
}

int moveDiscAnimation(int startPeg, int startPos, int endPeg, int endPos, int discNumber){
    int posX = positionOfPeg(startPeg);
    int posY = positionOfDisc(startPos);
    while (posY >= (screenHeight() * (1 - HEIGHT_OF_FLY))){
        posY--;
        updateAnimation(posX, posY, discNumber);
    }
    while (posX!=positionOfPeg(endPeg)){
        posX += moveDirection(startPeg,endPeg);
        updateAnimation(posX, posY, discNumber);
    }
    while (posY <= positionOfDisc(endPos)){
        posY++;
        updateAnimation(posX, posY, discNumber);
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

int checkActionCorrect(int pressPeg1, int pressPeg2){
    if((pressPeg1>=NUMBER_OF_PEGS) || (pressPeg2>=NUMBER_OF_PEGS) || (pressPeg1 < 0) || (pressPeg2 < 0)){
        return 0;
    }
    if(top[pressPeg1] == 0){
        return 0;
    }
    if(top[pressPeg2] == 0){
        return 1;
    }
    if(peak(pressPeg1) < peak(pressPeg2)){
        return 1;
    } else return 0;
}

int executeMove(int pegFrom, int pegOn){
    int movingDisc=pop(pegFrom);
    moveDiscAnimation(pegFrom, top[pegFrom], pegOn, top[pegOn], movingDisc);
    push(movingDisc, pegOn);
    return 0;
}

int main(){
    initGraph();
    initialMatrix();

    while(!isKeyDown(SDLK_ESCAPE)){

        drawBasicView();
        drawStaticDiscs();
        updateScreen();
        int pressPeg1 = keyDecode(getkey())-1;
        int pressPeg2 = keyDecode(getkey())-1;
        if(checkActionCorrect(pressPeg1, pressPeg2)){
            executeMove(pressPeg1, pressPeg2);
        }
    }
    return 0;
}

