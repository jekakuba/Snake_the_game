#pragma once

#include "Updatable.h"
#include "StaticObject.h"
class DynamicObject: 
	public StaticObject,
	public Movable,
	public Updatable
{
public:
	DynamicObject(const sf::Time& period, const Point& p = Point::NO_POINT);

};

