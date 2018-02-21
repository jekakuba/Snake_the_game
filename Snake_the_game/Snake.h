#pragma once

#include "Point.h"
#include "Direction.h"
#include "Interfaces.h"

#include <SFML/Graphics.hpp>
#include <list>

//Snake representation using a list
//Snake's head in front of the list and snake's tail in back of the list

class Snake: 
	public Drawable, 
	public Controllable,
	public Movable,
	public Reactable
{
public:
	using SnakeBody = std::list<Point>;
public:
	
	Snake(const Point& startPoint, const Direction::Dir startDir, int size);

	//changes direction. 
	//couldn't change direction to the opposite
	//if direction changed returns true
	bool changeDir(const Direction& d);

	//grows by one block
	//new block added to the tail 
	bool eat();

	void die();

	bool isAlive() const;
	
	//Using head pos and direction calculates next snake's head pos 
	Point nextHeadPos() const;
	
	Point head() const;
	const SnakeBody& body() const;

	void setHeadX(int x);
	void setHeadY(int y);

	//dissects snake by deleting block at specified position 
	//and disconnecting it's tail at that position
	//returns disconnected part
	//if position == head snake just dies
	SnakeBody dissect(SnakeBody::const_iterator& position);
public: //reactable implementation
	virtual bool reactOn(Reactor&) override;
public: //movable implementation
	virtual bool move() override;
public: //drawable implementation
	virtual void draw(sf::RenderWindow& window) const override;
public: //controllable implementation
	virtual bool keyPressed(const sf::Keyboard::Key&) override;

protected:
	//checks if snake's next head position coolides body
	bool checkSelfCollision() const;
private:
	std::list<Point> m_body;
	Direction m_dir;
	Point m_tail;
	bool m_isAlive;
};

