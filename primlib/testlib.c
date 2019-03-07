
#include "primlib.h"
#include"SDL.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if(initGraph())
	{
		exit(3);
	}
	int posX = 0;
	int radiusCircle = 50;
	int stoper = 0;
	int timeReff = 50;
	
	while(!isKeyDown(SDLK_ESCAPE) & stoper < 200)
	{
		filledRect(0, 0, screenWidth() - 1, screenHeight() - 1, BLACK);
		filledCircle(screenWidth() - ( screenWidth() / 100 * posX ), screenHeight() / 2, radiusCircle, YELLOW);
		updateScreen();
		posX = posX + 1;
		if(posX > 100)
		{
			posX = 0;
		}
		SDL_Delay(timeReff);
		stoper = stoper +1;
	}
	
	getkey();
	return 0;
}
