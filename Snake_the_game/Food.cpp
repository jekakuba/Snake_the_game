#include "Food.h"
#include "Draw_config.h"
#include "Snake.h"

void Food::draw(sf::RenderWindow& window) const {
	sf::RectangleShape rect(sf::Vector2f(DrawConfig::SCALE, DrawConfig::SCALE));
	rect.setFillColor(DrawConfig::FOOD_COLOR);
	rect.setPosition(sf::Vector2f(DrawConfig::to_viewport_coord(pos.x()),
								  DrawConfig::to_viewport_coord(pos.y()))
					);

	window.draw(rect);
}

bool Food::affect(Snake& s) {
	if (s.nextHeadPos() == pos) {
		s.eat();
		pos = Point::NO_POINT;
		return true;
	}

	return false;
}
