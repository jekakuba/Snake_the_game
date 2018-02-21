#pragma once
#include "Interfaces.h"
#include "Point.h"

//abstract class of an object placed on a game grid

class MapObject:
	public Drawable,
	public Reactor
{
public:
	MapObject();
	MapObject(const Point& p);
	Point pos;
};

