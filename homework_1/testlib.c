#include "primlib.h"
#include <stdlib.h>
#inclide <math.h>


#define REFRESH_TIME_IN_MS 30
#define VERTICLES_NUMBER 5


void drowFigure(int verticlesNumber, int angle, int figureSize){
	filledRect(0, 0, screenWidth() - 1, screenHeight() - 1, BLACK);
	
}


int main(int argc, char* argv[])
{
	if(initGraph())
	{
		exit(3);
	}
	
	
	while(!isKeyDown(SDLK_ESCAPE) )
	{
		
	}
	
	getkey();
	return 0;
}
