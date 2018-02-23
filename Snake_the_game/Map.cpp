#include "Map.h"
#include <iostream>
#include "Draw_config.h"

const sf::Time Map::GAME_UPDATE_RATE = sf::milliseconds(_GAME_UPDATE_RATE);

Map::Map(sf::RenderWindow& window, unsigned width, unsigned height,
	std::vector<std::unique_ptr<StaticObject>>&& mapObjects,
	std::vector<std::unique_ptr<DynamicObject>>&& dynObjects)
	:m_elapsedTime(sf::Time::Zero),
	 m_staticObjects(std::move(mapObjects)),
	 m_dynamicObjects(std::move(dynObjects)),
	 Module(window, width, height)
{
	load();
}

void Map::load() {
	m_snake.reset(new Snake(Point(8, 2), Direction::RIGHT, 6));
	m_food.reset(new Food);
	m_food->pos = generateFoodPos();
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

void Map::draw()
{
	if (!m_snake->isAlive()) {
		sf::RectangleShape rect(sf::Vector2f(DrawConfig::to_viewport_coord(m_width),
			DrawConfig::to_viewport_coord(m_height))
		);
		rect.setFillColor(sf::Color(255, 0, 0, 180));
		m_window.draw(rect);
	}

	for (auto& object : m_staticObjects) {
		object->draw(m_window);
	}

	for (auto& object : m_dynamicObjects) {
		object->draw(m_window);
	}

	m_snake->draw(m_window);
	m_food->draw(m_window);
}

void Map::update(const sf::Time& elapsed)
{
	if (!m_snake->isAlive()) {
		sf::sleep(sf::microseconds(GAME_OVER_DELAY));
		load();
		return;
	}

	if (m_snake->updateTimer(elapsed)) {
		for (auto& object : m_staticObjects) {
			m_snake->reactOn(*object);
		}

		if (m_snake->reactOn(*m_food)) {
			m_food->pos = generateFoodPos();
		}

		if (m_snake->isAlive()) {
			m_snake->move();
		}

		//draw();
	}

	for (auto& object : m_dynamicObjects) {
		if (object->update(elapsed)) {

			m_snake->reactOn(*object);

			if (m_snake->isChopped()) {
				auto objects = m_snake->dropRemains();
				for (auto& obj : objects) {
					m_staticObjects.push_back(std::unique_ptr<Food>(new Food(obj)));
				}
			}
			//draw();
		}
	}
}

void Map::catchInput(const sf::Keyboard::Key& k) {
	if (m_snake->isAlive() && m_snake->keyPressed(k)) {
		m_snake->resetTimer();
	}
}

void Map::handleInputEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) {
		catchInput(event.key.code);
	}
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

		for (auto& object : m_staticObjects) {
			if (object->pos == foodPos) {
				noCollisions = false;
				break;
			}
		}

	} while (noCollisions == false);

	return foodPos;
}

