#include "primlib.h"
#include <stdlib.h>

#define NUBER_OF_DISCS 4
#define NUMBER_OF_PEGS 3

#define HEIGH_OF_PEG_BASE 5
#define HEIGH_OF_PEG_STICK 50
#define DISTANCE_BEETWEN_PEGS 5
#define WIDTH_OF_PEG_STICK 6
#define BASE_OF_DISC 10


void drawDisc(int x, int y, int blockNumber){
    rect(x-BASE_OF_DISC/2*blockNumber, y, x+BASE_OF_DISC/2*blockNumber, y+HEIGH_OF_PEG_BASE);
}
int positionOfPeg(int peg){
    int x=peg*screenWidth()/NUMBER_OF_PEGS+DISTANCE_BEETWEN_PEGS;
    return x;
}
int positionOfDisc(int stockPosition) {
    int y = (stockPosition + 1) * HEIGH_OF_PEG_BASE;
    return y;
}
int main {
    int matrixOfpegs[NUMBER_OF_PEGS]
    return 0;
};

