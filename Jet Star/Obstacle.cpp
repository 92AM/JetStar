#include "StdAfx.h"
#include "Obstacle.h"

Obstacle::Obstacle(double initx, double inity, int r) : Element(initx,inity)
{
	radius = r;
	dx = (rand()%3)-3;
	dy = (rand()%3)-1;
	health = 4 + dx;

	//For Obsatacle Rotation:
	/*{angle = rand()%360;
	spin = 0;
	while(spin == 0)
		spin = ((rand()%10) - 5)/3.0;}*/
}