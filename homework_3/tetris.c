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


int getXSideLeft();
int getXSideRight();
int getYSize();
void drawBasicView();
void startTetris();
void drawSingleSquare(int x, int y, int color);
int detectColor(int color);
int getXPositionSquare(int x);
int getYPositionSquare(int y);
void drawTetris();
void drawNextBlock();
void draftBlock();
void start();
void findMid();
void writeInBlock(int moveDirection, int newRotation);
bool isCollision(int movDirection, int rotation);
bool isOutOfBox(block copyFallingBlock);
bool isBlockCollision(block copyFlyingBlock);
void convertDirections(int movDirection, int *movX, int *movY);


typedef struct block {
    int kind;
    int rotation;
    int midXPos;
    int midYPos;
    int xPosition;
    int yPosition;
} block;

static block fallingBlock;
static block nextBlock;

static int tetrisMatrix[TETRIS_HEIGHT][TETRIS_LENGTH];
extern const char blocks [7 /*kind */ ][4 /* rotation */ ][4][4];




int main() {

    if(initGraph()) {
        exit(3);
    }
    while (!isKeyDown(SDLK_ESCAPE)) {
        startTetris();
        drawTetris();
        draftBlock();
        drawNextBlock();
        getkey();
        updateScreen();
    }


    return 0;
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

void drawBasicView() {
    filledRect(0, 0, screenWidth(), screenHeight(), BLACK);
    line(getXSideLeft(), screenHeight(), getXSideLeft(), getYSize(), YELLOW);
    line(getXSideRight(), screenHeight(), getXSideRight(), getYSize(), YELLOW);
}

void startTetris() {
    for (int line = 0; line < TETRIS_LENGTH; ++line) {
        for (int column = 0; column < TETRIS_HEIGHT; ++column) {
            tetrisMatrix[line][column] = 0;
        }
    }
}

void drawSingleSquare(int x, int y, int color) {
    filledRect(x, y, x + SQUARE_SIZE - 1, y + SQUARE_SIZE - 1, color);
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

int getXPositionSquare(int x) {
    return (getXSideLeft() + 1 + x * SQUARE_SIZE);
}

int getYPositionSquare(int y) {
    return (screenHeight() - (y + 1) * SQUARE_SIZE);
}

void drawTetris() {
    drawBasicView();
    for (int line = 0; line < TETRIS_HEIGHT; ++line) {
        for (int column = 0; column < TETRIS_LENGTH; ++column) {
            drawSingleSquare(getXPositionSquare(column), getYPositionSquare(line), detectColor(tetrisMatrix[line][column]));
        }
    }
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

void draftBlock() {
    fallingBlock = nextBlock;
    nextBlock.kind = rand() % NUMBER_OF_BLOCKS;
    nextBlock.rotation = rand() % NUMBER_OF_ROTATIONS;
}

void start() {
    startTetris();
    drawNextBlock();
    drawNextBlock();
    fallingBlock.xPosition = TETRIS_LENGTH / 2;
    fallingBlock.yPosition = TETRIS_HEIGHT - 1;
}

void findMid() {
    for (int line = 0; line < BLOCK_SIZE; ++line) {
        for (int column = 0; column < BLOCK_SIZE; ++column) {
            if (blocks[fallingBlock.kind][fallingBlock.rotation][line][column] == 2) {
                fallingBlock.midXPos = column;
                fallingBlock.midYPos = line;
            }
        }
    }
}

bool isOutOfBox(block copyFallingBlock) {
    bool leftOut;
    bool rightOut;
    bool downOut;
    if (copyFallingBlock.xPosition - copyFallingBlock.midXPos < 0) {
        leftOut = true;
    }
    for (int line = 0; line < SQUARE_SIZE; ++line) {
        for (int column = 0; column < SQUARE_SIZE; ++column) {
            if (blocks[copyFallingBlock.kind][copyFallingBlock.rotation][line][column] != 0) {
                if ((copyFallingBlock.xPosition - copyFallingBlock.midXPos + column) >= TETRIS_LENGTH) {
                    rightOut = true;
                }
                if ((copyFallingBlock.yPosition - copyFallingBlock.midYPos + line) < 0) {
                    downOut = true;
                }
            }
        }
    }
    if (leftOut || rightOut || downOut) {
        return false;
    } else {
        return true;
    }

}

bool isBlockCollision(block copyFlyingBlock) {
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

void convertDirections(int movDirection, int *movX, int *movY) {
    switch (movDirection) {
        case 2:
            *movY = - 1;
            break;
        case 4:
            *movX = - 1;
            break;
        case 6:
            *movX = 1;
            break;
        case 8:
            *movY = 1;
    }
}



bool isCollision(int movDirection, int rotation) {
    block copyFallingBlock = fallingBlock;
    int movX = 0;
    int movY = 0;
    convertDirections(movDirection, &movX, &movY);
    copyFallingBlock.xPosition = copyFallingBlock.xPosition + movX;
    copyFallingBlock.yPosition = copyFallingBlock.yPosition + movY;
    copyFallingBlock.rotation = rotation;
    if (isOutOfBox(copyFallingBlock)) {
        return true;
    }
    if (isBlockCollision(copyFallingBlock)) {
        return true
    }
    return false;
}

bool writeInBlock(int moveDirection, int newRotation) {
    findMid();
    if (!isCollision(moveDirection , newRotation)) {
        for (int line = 0; line < BLOCK_SIZE; ++line) {
            for (int column = 0; column < BLOCK_SIZE; ++column) {
                if (blocks[fallingBlock.kind][fallingBlock.rotation][line][column] != 0) {
                    tetrisMatrix[fallingBlock.yPosition - fallingBlock.midYPos][fallingBlock.xPosition - fallingBlock.midXPos] = blocks[fallingBlock.kind][fallingBlock.rotation][line][column];
                }
            }
        }
        return true;
    } else {
        return false;
    }
}