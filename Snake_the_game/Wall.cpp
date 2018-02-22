#include "Wall.h"
#include "Draw_config.h"
#include "Snake.h"

Wall::Wall(const Point& p) : StaticObject(p) {}

void Wall::draw(sf::RenderWindow& window) const {
	sf::RectangleShape rect(sf::Vector2f(DrawConfig::SCALE, DrawConfig::SCALE));
	rect.setFillColor(DrawConfig::WALL_COLOR);
	rect.setPosition(sf::Vector2f(DrawConfig::to_viewport_coord(pos.x()),
		DrawConfig::to_viewport_coord(pos.y()))
	);

	window.draw(rect);
}

bool Wall::affect(Snake& s) {
	if (s.nextHeadPos() == pos) {
		s.die();
		return true;
	}
	return false;
}