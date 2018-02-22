#pragma once

#include "MapObject.h"
#include "Direction.h"
class Map;
class Saw:  
	public MapObject,
	public Movable 
{
public:
	Saw(const Point& from, const Point& to, Map& t);
public: //Movable implementation
	virtual bool move() override;
public: //Drawable implementation
	virtual void draw(sf::RenderWindow&) const override;
public: //Reactor
	virtual bool affect(Snake& s);
private:
	Point m_from;
	Point m_to;
	Direction m_direction;
	Map& m_map;
};

