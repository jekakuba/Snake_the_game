#pragma once

#include "DynamicObject.h"
#include "Direction.h"
class Map;
class CircularSaw : public DynamicObject {
public:
	CircularSaw(const Point& from, const Point& to, const sf::Time& speed = sf::milliseconds(150));
public: //Updatable implementation
	virtual bool update(const sf::Time& dt) override;
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
	Map* m_map;
};

