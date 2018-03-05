#include "gwin.h"
#include "StdAfx.h"
#include "Element.h"

Element::Element(double initx, double inity)
{
	x = initx;
	y = inity;
}

void Element::move(double _dx, double _dy)
{
	x += _dx;
	y += _dy;
}