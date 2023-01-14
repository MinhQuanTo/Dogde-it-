#include "asteroid.h"

asteroid::asteroid() // define direction of asteroid
{
	dx = rand() % 8 - 4;
	dy = rand() % 8 - 4;
	name = "asteroid";
}

void asteroid::update() // update direction
{
	x += dx;
	y += dy;
	if (x > screenWidth)
	{
		x = 0;
	}

	if (x < 0)
	{
		x = screenWidth;
	}

	if (y > screenHeight)
	{
		y = 0;
	}

	if (y < 0)
	{
		y = screenHeight;
	}
}
