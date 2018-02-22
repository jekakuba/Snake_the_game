#pragma once
#define interface struct

class Snake;
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>


interface Drawable {
	//draws object in RenderWindow
	virtual void draw(sf::RenderWindow&) const = 0;
};

interface Controllable {
	//Returns true if pressed key somehow affects object
	//otherwise retruns false
	virtual bool keyPressed(const sf::Keyboard::Key&) = 0;
};

interface Movable {
	//Returns true if position has been changed
	//Otherwise returns false
	virtual bool move() = 0;
};

//Visitor pattern interfaces
interface Reactor {
	//returns ReactOn status
	virtual bool affect(Snake&) = 0;
};

interface Reactable {
	//returns true if reactor somehow affects object
	//otherwise returns false
	virtual bool reactOn(Reactor& r) = 0;
};
