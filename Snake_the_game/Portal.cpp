#include "Portal.h"

#include "Draw_config.h"
#include "Snake.h"

Portal::Portal() : m_exitPortal(nullptr) {

}

Portal::Portal(const Point& p) : MapObject(p), m_exitPortal(nullptr) {

}

void Portal::connectWith(Portal& other) {
	m_exitPortal = &other;
	other.m_exitPortal = this;
}

bool Portal::hasExit() const {
	return m_exitPortal == nullptr;
}

void Portal::draw(sf::RenderWindow& window) const {
	sf::RectangleShape rect(sf::Vector2f(DrawConfig::SCALE, DrawConfig::SCALE));
	rect.setFillColor(DrawConfig::PORTAL_COLOR);
	rect.setPosition(sf::Vector2f(DrawConfig::to_viewport_coord(pos.x()),
								  DrawConfig::to_viewport_coord(pos.y()))
	);

	window.draw(rect);
}

bool Portal::affect(Snake& s) {
	if(s.nextHeadPos() == this->pos) {
		/*if(!hasExit()) {
			s.die();
			return true;
		}*/

		Point outPos = m_exitPortal->pos;

		s.move();
		s.setHeadX(outPos.x()), s.setHeadY(outPos.y());
	
		return true;
	}

	return false;
}