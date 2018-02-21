#include "Snake.h"
#include "Draw_config.h"

Snake::Snake(const Point& startPoint, const Direction::Dir startDir, int size)
			 :m_dir(startDir),
			  m_isAlive(true)
{
	for (int i = 0; i < size; ++i) {
		m_body.push_back(startPoint + m_dir.to_point().reversed() * i);
	}

	m_tail = startPoint + m_dir.to_point().reversed() * size;
}

bool Snake::changeDir(const Direction& d) {
	//change only if new direction is not opposite to current
	if ((m_dir.to_point() + d.to_point()) != Point(0, 0)) {
		m_dir = d;
		return true;
	}
	return false;
}

bool Snake::eat() {
	if (m_tail != Point::NO_POINT) {
		m_body.push_back(m_tail);
		m_tail = Point::NO_POINT;
		return true;
	}
	return false;
}

void Snake::die() {
	m_isAlive = false;
}

bool Snake::isAlive() const {
	return m_isAlive;
}

Point Snake::nextHeadPos() const {
	return m_body.front() + m_dir.to_point();
}

Point Snake::head() const {
	return m_body.front();
}

bool Snake::checkSelfCollision() const {
	auto head = nextHeadPos();
	
	for (auto iter = ++m_body.begin(); iter != m_body.end(); ++iter) {
		if (*iter == head)
			return true;
	}

	return false;
}

Snake::SnakeBody Snake::dissect(SnakeBody::const_iterator& position) {
	SnakeBody remains;

	if (position == m_body.begin()) {
		die();
		return remains;
	}
	//dissection goes here
	remains.splice(remains.begin(), m_body, position, m_body.end());
	
	//removing block at dissection point
	if (!remains.empty()) {
		remains.pop_front();
	}

	return remains;
}

bool Snake::move() {
	if (checkSelfCollision() == false) {
		m_body.push_front(m_body.front() + m_dir.to_point());
		m_tail = m_body.back();
		m_body.pop_back();
		return true;
	}
	return false;
}

const std::list<Point>& Snake::body() const {
	return m_body;
}

void Snake::draw(sf::RenderWindow& window) const {
	sf::RectangleShape baseRect(sf::Vector2f(DrawConfig::SCALE, DrawConfig::SCALE));
	baseRect.setFillColor(DrawConfig::SNAKE_COLOR);

	for (const auto &i : m_body) {
		baseRect.setPosition(sf::Vector2f(DrawConfig::to_viewport_coord(i.x()),
										  DrawConfig::to_viewport_coord(i.y()))
							);

		window.draw(baseRect);
	}
}

void Snake::setHeadX(int x) {
	m_body.front().x(x);
}

void Snake::setHeadY(int y) {
	m_body.front().y(y);
}

bool Snake::keyPressed(const sf::Keyboard::Key& key) {
	switch (key) {
		case sf::Keyboard::W:
		case sf::Keyboard::Up:
			return changeDir(Direction::UP);
			

		case sf::Keyboard::S:
		case sf::Keyboard::Down:
			return changeDir(Direction::DOWN);
		

		case sf::Keyboard::D:
		case sf::Keyboard::Right:
			return changeDir(Direction::RIGHT);
		

		case sf::Keyboard::A:
		case sf::Keyboard::Left:
			return changeDir(Direction::LEFT);
			

		default:
			return false;
	}
}

bool Snake::reactOn(Reactor& r) {
	return r.affect(*this);
}

