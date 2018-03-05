#pragma once

#include "Element.h"

class Obstacle : public Element
{
public:
	Obstacle(double initx, double inity, int r);

	int radius;
	//double angle;
	//double spin;
};
