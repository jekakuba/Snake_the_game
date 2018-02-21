#pragma once

#include "Point.h"

//class that represents direciton on a game board
//with considering y axis grows down and x axis grows right

class Direction {
public:
	using Dir = enum { UP, LEFT, DOWN, RIGHT };
public:
	Direction(const Dir& d);
	Direction& operator=(const Dir& d);

	Dir get_dir() const;

	//converts direction to directing unit vector
	Point to_point() const;
	
private:
	Dir m_direction;
};

