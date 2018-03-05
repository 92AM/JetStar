#include "StdAfx.h"
#include "Jet.h"
#include "Missile.h"

Jet::Jet(double initx, double inity) : Element(initx,inity)
{
	dx = 0;
	dy = 0;
	health = 5;
}

void Jet::shoot(double _x, double _y, int hp)
{
	missiles.push_back(Missile(_x,_y,hp));//add missile
}