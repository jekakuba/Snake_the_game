#pragma once

#include "MapObject.h"

class Wall : public MapObject {
public:
	Wall() = default;
	Wall(const Point& p);
public: //Drawable implementation
	virtual void draw(sf::RenderWindow& window) const override;
public: //Reactor implementation
	virtual bool affect(Snake&) override;
};

