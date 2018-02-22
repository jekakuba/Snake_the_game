#include "Saw.h"
#include "Draw_config.h"
#include "Snake.h"

#include <iostream>


Saw::Saw(const Point& from, const Point&to, Map& m) 
	: MapObject(from),
	  m_from(from),
	  m_to(to),
	  m_direction(Direction::from(m_from, m_to)),
	  m_map(m)
{
	
}

bool Saw::move() {
	if(pos == m_to) {
		std::swap(m_from, m_to);
		m_direction = Direction::from(m_from, m_to);
	}

	pos += m_direction.to_point();

	return true;
}

void Saw::draw(sf::RenderWindow& window) const {

	sf::RectangleShape rect(sf::Vector2f(DrawConfig::SCALE, DrawConfig::SCALE));
	rect.setFillColor(DrawConfig::SAW_PATH_COLOR);

	Point temp = m_from;

	while(temp != m_to + m_direction.to_point()) {
		rect.setPosition(sf::Vector2f(DrawConfig::to_viewport_coord(temp.x()),
									  DrawConfig::to_viewport_coord(temp.y())));

		window.draw(rect);
		temp += m_direction.to_point();
	}

	rect.setFillColor(DrawConfig::SAW_COLOR);
	rect.setPosition(sf::Vector2f(DrawConfig::to_viewport_coord(pos.x()),
								  DrawConfig::to_viewport_coord(pos.y()))
	);

	window.draw(rect);
}

bool Saw::affect(Snake& s) {
	if(s.nextHeadPos() == pos) {
		s.die();
		return true;
	}
	for(auto it = s.body().begin(); it != s.body().end(); ++it) {
		if(pos == *it) {
			s.dissect(it);
			return true;
		}
	}

	return false;
}

