#pragma once
#include <SFML/System.hpp>

class Updatable
{
public:
	Updatable(const sf::Time& period);
	virtual bool update(const sf::Time& deltaTime) = 0;

	bool updateTimer(const sf::Time& deltaTime);
	void resetTimer();
private:
	sf::Time m_timePassed;
	sf::Time m_period;
};

