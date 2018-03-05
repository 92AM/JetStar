#pragma once

#include "Element.h"
#include "Missile.h"

class Jet: public Element
{
public:
	Jet(double initx, double inity);

	void shoot(double _x, double _y, int hp);

	std::vector<Missile> missiles;
};
