#pragma once
#include "Food.h"
#include "Wall.h"
#include "Snake.h"
#include "Interfaces.h"
#include "RandomGenerator.h"
#include "Portal.h"
#include "CircularSaw.h"
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <memory>
#include <random>

//represents level
//should be refactored

class Map {
	static constexpr unsigned int _GAME_UPDATE_RATE = 300; //ms
	static constexpr unsigned int GAME_OVER_DELAY = 1000; //ms
public:
	//Map(unsigned width, unsigned height);
	Map(sf::RenderWindow& window, unsigned width, unsigned height,
		std::vector<std::unique_ptr<StaticObject>>&& mapObjects,
		std::vector<std::unique_ptr<DynamicObject>>&& dynObjects);

	void update(const sf::Time& elapsed);
	void draw() const;

	void catchInput(const sf::Keyboard::Key&);

	void load();
protected:
	Point generateFoodPos();
	bool reflectSnake();
private:
	std::unique_ptr<Snake> m_snake;
	std::unique_ptr<Food> m_food;
	std::vector<std::unique_ptr<StaticObject>> m_staticObjects;
	std::vector<std::unique_ptr<DynamicObject>> m_dynamicObjects;
	sf::RenderWindow& m_window;

	RandomGenerator m_rand;
	sf::Time m_elapsedTime;
	unsigned m_width;
	unsigned m_height;
private:
	static const sf::Time GAME_UPDATE_RATE;
};

