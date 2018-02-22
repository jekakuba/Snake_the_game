#pragma once

#include "StaticObject.h"

class Wall : public StaticObject {
public:
	Wall() = default;
	Wall(const Point& p);
public: //Drawable implementation
	virtual void draw(sf::RenderWindow& window) const override;
public: //Reactor implementation
	virtual bool affect(Snake&) override;
};

