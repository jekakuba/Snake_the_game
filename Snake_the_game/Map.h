#pragma once
#include "Food.h"
#include "Wall.h"
#include "Snake.h"
#include "Interfaces.h"
#include "RandomGenerator.h"
#include "Portal.h"
#include "Saw.h"
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <memory>
#include <random>

//represents level
//should be refactored

class Map : public Drawable {
	static constexpr unsigned int _GAME_UPDATE_RATE = 300; //ms
	static constexpr unsigned int GAME_OVER_DELAY = 1000; //ms
public:
	Map(unsigned m_width, unsigned m_height);

	void update(sf::Time&& elapsed);
	virtual void draw(sf::RenderWindow& window) const override;

	void catchInput(const sf::Keyboard::Key&);

	void load();
protected:
	Point generateFoodPos();
	bool reflectSnake();
private:
	std::unique_ptr<Snake> m_snake;
	std::unique_ptr<Food> m_food;
	std::vector<Wall> m_walls;
	std::vector<Portal> m_portals;
	Saw m_saw;

	RandomGenerator m_rand;
	sf::Time m_elapsedTime;
	unsigned m_width;
	unsigned m_height;
private:
	static const sf::Time GAME_UPDATE_RATE;
};

