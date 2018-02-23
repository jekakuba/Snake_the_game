#pragma once
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

class Module
{
public:
	Module(sf::RenderWindow& window, unsigned width, unsigned height);

	virtual void draw() = 0;
	virtual void update(const sf::Time&) = 0;
	virtual void handleInputEvent(sf::Event&) = 0;
protected:
	unsigned m_width;
	unsigned m_height;
	sf::RenderWindow& m_window;
};

