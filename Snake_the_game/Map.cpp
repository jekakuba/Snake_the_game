#include "Map.h"
#include <iostream>
#include "Draw_config.h"

const sf::Time Map::GAME_UPDATE_RATE = sf::milliseconds(_GAME_UPDATE_RATE);

Map::Map(unsigned width, unsigned height) 
				  :m_elapsedTime(sf::Time::Zero),
				   m_width(width),
				   m_height(height),
				   m_saw(Point(10,2), Point(10,10), *this)
{
	load();

	for (int x = 0; x < m_width; ++x) {
		m_walls.push_back(Wall(Point(x, 0)));
		m_walls.push_back(Wall(Point(x, m_height - 1)));
	}

	for (int y = 0; y < m_height; ++y) {
		m_walls.push_back(Wall(Point(0, y)));
		m_walls.push_back(Wall(Point(m_width - 1, y)));
	}

	m_portals.push_back(Portal(Point(5, 5)));
	m_portals.push_back(Portal(Point(m_width - 5, m_height - 5)));



	m_portals.front().connectWith(m_portals.back());
	
	Point mapCenter = Point((m_width - 2) / 2, (m_height - 2) / 2);
	
	for (int x = mapCenter.x() - 8; x <= mapCenter.x() + 8; ++x) {
		m_walls.push_back(Point(x, mapCenter.y()));
	}

	for (int y = mapCenter.y() - 4; y <= mapCenter.y() + 4; ++y) {
		m_walls.push_back(Point(mapCenter.x(), y));
	}

}

void Map::load() {
	m_snake.reset(new Snake(Point(8, 2), Direction::RIGHT, 6));

	m_food.reset(new Food);
	m_food->pos = generateFoodPos();
}

void Map::update(sf::Time&& elapsed) {
	m_elapsedTime += elapsed;
	
	if (!m_snake->isAlive()) {
		if (m_elapsedTime > sf::milliseconds(GAME_OVER_DELAY)) {
			load();
		}
		return;
	}

	if (m_elapsedTime > GAME_UPDATE_RATE) {
		m_elapsedTime = sf::Time::Zero;

		for (auto& wall : m_walls) {
			m_snake->reactOn(wall);
		}
	
		for(auto& portal : m_portals) {
			m_snake->reactOn(portal);
		}

		m_saw.move();
		m_snake->reactOn(m_saw);

		if (m_snake->reactOn(*m_food)) {
			m_food->pos = generateFoodPos();
		}

		if (m_snake->isAlive()) {
			if (!m_snake->move()) {
				m_snake->die();
			}
		}

	}
}

void Map::catchInput(const sf::Keyboard::Key& k) {
	if (m_snake->isAlive() && m_snake->keyPressed(k)) {
		m_elapsedTime = GAME_UPDATE_RATE;
	}
}

bool Map::reflectSnake() {
	if (m_snake->nextHeadPos().x() < 0
	|| m_snake->nextHeadPos().x() >= m_width
	|| m_snake->nextHeadPos().y() < 0
	|| m_snake->nextHeadPos().y() >= m_height) {
		m_snake->die();
		return false;
	}

	return true;
}

Point Map::generateFoodPos() {
	bool noCollisions;
	Point foodPos;
	
	do {
		noCollisions = true;
		foodPos = m_rand.generatePoint(Point(0, 0), Point(m_width, m_height));
	
		for (auto& snakePart : m_snake->body()) {
			if (snakePart == foodPos) {
				noCollisions = false;
				break;
			}
		}

		for (auto& wall : m_walls) {
			if (wall.pos == foodPos) {
				noCollisions = false;
				break;
			}
		}

	} while (noCollisions == false);

	return foodPos;
}

void Map::draw(sf::RenderWindow& window) const {
	if (!m_snake->isAlive()) {
		sf::RectangleShape rect(sf::Vector2f(DrawConfig::to_viewport_coord(m_width),
										DrawConfig::to_viewport_coord(m_height))
		);

		rect.setFillColor(sf::Color(255, 0, 0, 180));
		window.draw(rect);
	}

	m_saw.draw(window);
	m_snake->draw(window);
	m_food->draw(window);

	for (auto& wall : m_walls) {
		wall.draw(window);
	}

	for(auto& portal : m_portals) {
		portal.draw(window);
	}
}

