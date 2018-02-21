#pragma once

#include "MapObject.h"

class Food : public MapObject {
public: //Drawable implementation
	virtual void draw(sf::RenderWindow& window) const override;
public: //Reactor implementation
	virtual bool affect(Snake&) override;
};

