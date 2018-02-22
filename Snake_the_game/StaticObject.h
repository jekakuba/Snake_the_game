#pragma once
#include "Interfaces.h"
#include "Point.h"

//abstract class of an object placed on a game grid

class StaticObject:
	public Drawable,
	public Reactor
{
public:
	StaticObject();
	StaticObject(const Point& p);
	Point pos;
};

