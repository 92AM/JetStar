#include "StdAfx.h"
#include "Missile.h"

Missile::Missile(double initx, double inity, int hp) : Element(initx,inity)
{
	dx = 20;
	dy = 0;
	health = hp;
}