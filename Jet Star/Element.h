#pragma once

class Element
{
public:
	Element(double initx, double inity);

	double x;
	double y;
	double dx;
	double dy;
	int health;

	void move(double _dx, double _dy);
};
