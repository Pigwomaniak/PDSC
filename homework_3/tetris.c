//
// Created by maciek on 04/04/19.
//

#include "primlib.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define TETRIS_HEIGHT 20
#define TETRIS_LENGTH 10
#define SQUARE_SIZE 30
#define BLOCK_SIZE 4
#define NUMBER_OF_BLOCKS 7
#define NUMBER_OF_ROTATIONS 4
#define START_FALL (screenWidth()/2)
#define MOV_RIGHT 1
#define MOV_LEFT 2
#define MOV_DOWN 3
#define ROTATE 4
#define BLOCK_IS_DOWN 1
#define BLOCK_IS_SIDE 2

typedef struct block {
    int kind;
    int rotation;
    int midXPos;
    int midYPos;
    int xPosition;
    int yPosition;
} block;


int getXSideLeft();
int getXSideRight();
int getYSize();
void drawBasicView();
void startTetris();
void drawSingleSquare(int x, int y, int color);
int detectColor(int color);
int getXDynamicSquare(int x);
int getYDynamicSquare(int y);
void drawTetris();
void drawNextBlock();
void draftBlock();
void start();
void findMid(block *blockName);
int getXPositionSquare(int line);
int getYPositionSquare(int column);
void drawDynamicBlock();
bool writeInBlock(int moveDirection, int newRotation);
int isCollision(int movDirection, int rotation);
int isOutOfBox(block copyFallingBlock);
bool isBlockCollision(block copyFlyingBlock);
void convertDirections(int movDirection, int *movX, int *movY);
int moveProcedure(int move);
int updateBlock(int movDirection, int newRotation);
int detectMove();
int makeBlockStatic();


static block fallingBlock;
static block nextBlock;


static int tetrisMatrix[TETRIS_HEIGHT][TETRIS_LENGTH];
extern const char blocks [7 /*kind */ ][4 /* rotation */ ][4][4];

int main() {

    if(initGraph()) {
        exit(3);
    }
    start();
    tetrisMatrix[1][1] = 3;
    while (!isKeyDown(SDLK_ESCAPE)) {
        int move = detectMove();
        if (move != -1) {
            moveProcedure(move);
        }
        drawTetris();
        updateScreen();
        getkey();
    }
    return 0;
}

void start() {
    startTetris();
    draftBlock();
    draftBlock();
}

void startTetris() {
    for (int line = 0; line < TETRIS_LENGTH; ++line) {
        for (int column = 0; column < TETRIS_HEIGHT; ++column) {
            tetrisMatrix[line][column] = 0;
        }
    }
}

void draftBlock() {
    fallingBlock = nextBlock;
    nextBlock.kind = rand() % NUMBER_OF_BLOCKS;
    nextBlock.rotation = rand() % NUMBER_OF_ROTATIONS;
    fallingBlock.xPosition = TETRIS_LENGTH / 2;
    fallingBlock.yPosition = TETRIS_HEIGHT - 1;
    findMid(&fallingBlock);
}

int detectMove() {
    if (isKeyDown(SDLK_SPACE)) {
        return ROTATE;
    }
    if (isKeyDown(SDLK_a)) {
        return MOV_LEFT;
    }
    if (isKeyDown(SDLK_s)) {
        return MOV_DOWN;
    }
    if (isKeyDown(SDLK_d)) {
        return MOV_RIGHT;
    }
    return -1;
}

int moveProcedure(int move) {
    int direction = 0;
    int newRotation = fallingBlock.rotation;
    if(move != ROTATE) {
        direction = move;
    } else {
        newRotation = (fallingBlock.rotation + 1) % 4;
    }
    writeInBlock(direction, newRotation);
    return 0;
}

bool writeInBlock(int moveDirection, int newRotation) {
    findMid(&fallingBlock);
    int blockStatus = isCollision(moveDirection , newRotation);
    if (!blockStatus) {
        updateBlock(moveDirection, newRotation);
        drawDynamicBlock();
        return 1;
    } else if(blockStatus == BLOCK_IS_DOWN) {
        makeBlockStatic();
        draftBlock();
        return 1;
    } else {
        return 0;
    }
}

int isCollision(int movDirection, int rotation) {
    block copyFallingBlock = fallingBlock;
    int movX = 0;
    int movY = 0;
    convertDirections(movDirection, &movX, &movY);
    copyFallingBlock.xPosition = copyFallingBlock.xPosition + movX;
    copyFallingBlock.yPosition = copyFallingBlock.yPosition + movY;
    copyFallingBlock.rotation = rotation;
    findMid(&copyFallingBlock);
    int outOfBox = isOutOfBox(copyFallingBlock);
    if (outOfBox) {
        return outOfBox;
    }
    if (isBlockCollision(copyFallingBlock)) {
        return BLOCK_IS_DOWN;
    }
    return 0;
}

bool isBlockCollision(block copyFallingBlock) {
    for (int line = 0; line < BLOCK_SIZE; ++line) {
        for (int column = 0; column < BLOCK_SIZE; ++column) {
            bool isStaticBlock = blocks[copyFallingBlock.kind][copyFallingBlock.rotation][line][column] == 3;
            bool isMovingBlock = tetrisMatrix[copyFallingBlock.yPosition - copyFallingBlock.midYPos][copyFallingBlock.xPosition - copyFallingBlock.midXPos] == 0;
            if (isStaticBlock && isMovingBlock) {
                return true;
            }
        }
    }
    return false;
}

int isOutOfBox(block copyFallingBlock) {
    bool leftOut = false;
    bool rightOut = false;
    bool downOut = false;
    if (copyFallingBlock.xPosition - copyFallingBlock.midXPos < 0) {
        leftOut = true;
    }
    for (int line = 0; line < BLOCK_SIZE; ++line) {
        for (int column = 0; column < BLOCK_SIZE; ++column) {
            if (blocks[copyFallingBlock.kind][copyFallingBlock.rotation][line][column] != 0) {
                if ((copyFallingBlock.xPosition - copyFallingBlock.midXPos + column) > (TETRIS_LENGTH - 1)) {
                    rightOut = true;
                }
                if ((copyFallingBlock.yPosition - copyFallingBlock.midYPos + line) < 1) {
                    downOut = true;
                }
            }
        }
    }
    if (downOut) {
        return BLOCK_IS_DOWN;
    }
    if (leftOut || rightOut) {
        return BLOCK_IS_SIDE;
    } else {
        return 0;
    }
}

void drawTetris() {
    drawBasicView();
    for (int line = 0; line < TETRIS_HEIGHT; ++line) {
        for (int column = 0; column < TETRIS_LENGTH; ++column) {
            drawSingleSquare(getXPositionSquare(column), getYPositionSquare(line), detectColor(tetrisMatrix[line][column]));
        }
    }
    drawDynamicBlock();
    drawNextBlock();
}

void drawBasicView() {
    filledRect(0, 0, screenWidth(), screenHeight(), BLACK);
    line(getXSideLeft() - 1, screenHeight(), getXSideLeft() - 1, getYSize(), YELLOW);
    line(getXSideRight(), screenHeight(), getXSideRight(), getYSize(), YELLOW);
}

void drawNextBlock() {
    int nexBlockXPosition = getXSideRight() + (screenWidth() - getXSideRight()) / 2 - 2 * SQUARE_SIZE;
    for (int line = 0; line < BLOCK_SIZE; ++line) {
        for (int column = 0; column < BLOCK_SIZE; ++column) {
            int color = detectColor(blocks[nextBlock.kind][nextBlock.rotation][line][column]);
            drawSingleSquare(nexBlockXPosition + column * SQUARE_SIZE, getYSize() + line * SQUARE_SIZE, color);
        }
    }
}

void drawDynamicBlock() {
    for (int line = 0; line < BLOCK_SIZE; ++line) {
        for (int column = 0; column < BLOCK_SIZE; ++column) {
            int color = detectColor(blocks[fallingBlock.kind][fallingBlock.rotation][line][column]);
            if(color != BLACK){
                drawSingleSquare(getXDynamicSquare(column), getYDynamicSquare(line), color);
            }
        }
    }
}

int getXPositionSquare(int x) {
    return (getXSideLeft() + 1 + x * SQUARE_SIZE);
}

int getYPositionSquare(int y) {
    return (screenHeight() - (y + 1) * SQUARE_SIZE);
}

int detectColor(int color) {
    switch (color) {
        case 0:
            return BLACK;
        case 1:
            return BLUE;
        case 2:
            return GREEN;
        case 3:
            return RED;
        default:
            return 0;
    }
}

int getXSideLeft() {
    return (((screenWidth() - TETRIS_LENGTH * SQUARE_SIZE) / 2) - 1);
}

int getXSideRight() {
    return (screenWidth() - (screenWidth() - TETRIS_LENGTH * SQUARE_SIZE) / 2);
}

int getYSize() {
    return (screenHeight() - TETRIS_HEIGHT * SQUARE_SIZE);
}

void drawSingleSquare(int x, int y, int color) {
    filledRect(x, y, x + SQUARE_SIZE - 1, y + SQUARE_SIZE - 1, color);
}

int getXDynamicSquare(int line) {
    return (getXSideLeft() + (fallingBlock.xPosition - fallingBlock.midXPos + line) * SQUARE_SIZE);
}

int getYDynamicSquare(int column) {
    return (screenHeight() - (fallingBlock.yPosition - fallingBlock.midYPos +column) * SQUARE_SIZE);
}








void findMid( block *blockName) {
    for (int line = 0; line < BLOCK_SIZE; ++line) {
        for (int column = 0; column < BLOCK_SIZE; ++column) {
            if (blocks[blockName->kind][blockName->rotation][line][column] == 2) {
                blockName->midXPos = column;
                blockName->midYPos = line;
            }
        }
    }
}





void convertDirections(int movDirection, int *movX, int *movY) {
    switch (movDirection) {
        case MOV_DOWN:
            *movY = - 1;
            break;
        case MOV_LEFT:
            *movX = - 1;
            break;
        case MOV_RIGHT:
            *movX = 1;
            break;
    }
}

int updateBlock(int movDirection, int newRotation) {
    int movX = 0;
    int movY = 0;
    convertDirections(movDirection, &movX, &movY);
    fallingBlock.xPosition += movX;
    fallingBlock.yPosition += movY;
    fallingBlock.rotation = newRotation;
    findMid(&fallingBlock);
    return 0;
}

int makeBlockStatic() {
    for (int line = 0; line < BLOCK_SIZE; ++line) {
        for (int column = 0; column < BLOCK_SIZE; ++column) {
            if (blocks[fallingBlock.kind][fallingBlock.rotation][line][column] != 0) {
                tetrisMatrix[fallingBlock.yPosition - fallingBlock.midYPos + line][fallingBlock.xPosition -fallingBlock.midXPos + column] = 3;
            }
        }
    }
    return 0;
}





