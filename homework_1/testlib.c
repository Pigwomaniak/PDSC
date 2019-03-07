#include "primlib.h"
#include <stdlib.h>
#include <math.h>


#define REFRESH_TIME_IN_MS  20
#define VERTICLES_NUMBER    5
#define FIGURE_START_SIZE   50


float figureRotationAngle=0;
float figureScale=1;


void drowFigure(int verticlesNumber, float angle, int figureSize){
    float figurePoints[verticlesNumber] [2];
	filledRect(0, 0, screenWidth() - 1, screenHeight() - 1, BLACK);
	for(int currentPoint=0; currentPoint<verticlesNumber; currentPoint=currentPoint+1)
    {
            figurePoints[currentPoint][0]=cos(2*M_PI/verticlesNumber*currentPoint+angle)*figureSize+screenWidth()/2;
            figurePoints[currentPoint][1]=sin(2*M_PI/verticlesNumber*currentPoint+angle)*figureSize+screenHeight()/2;
    }
    for(int currentPoint=0; currentPoint<verticlesNumber; currentPoint=currentPoint+1)
    {
            line(figurePoints[currentPoint][0],figurePoints[currentPoint][1],figurePoints[(currentPoint+1)%verticlesNumber][0],figurePoints[(currentPoint+1)%verticlesNumber][1],GREEN);
    }
    
    updateScreen();
}


int main(int argc, char* argv[])
{
    int incrisingSize=1;
    int rotationDirection=1;
    
	if(initGraph())
	{
		exit(3);
	}

	while(!isKeyDown(SDLK_ESCAPE) )
	{
		drowFigure(VERTICLES_NUMBER,figureRotationAngle,FIGURE_START_SIZE*figureScale);
        
        figureScale=figureScale+0.05*incrisingSize;
        if(figureScale>4)
        {
            incrisingSize=-1;
        }
        if(figureScale<0.4)
        {
            incrisingSize=1;
        }

        figureRotationAngle=figureRotationAngle+M_PI/100*rotationDirection;
        if(figureRotationAngle>2*M_PI/VERTICLES_NUMBER)
        {
            figureRotationAngle=0;
        }
        if(isKeyDown(SDLK_a))
        {
            rotationDirection=-1;
        }
        if(isKeyDown(SDLK_d))
        {
            rotationDirection=1;
        }
        
        SDL_Delay(REFRESH_TIME_IN_MS);
	}
	
	getkey();
	return 0;
}
