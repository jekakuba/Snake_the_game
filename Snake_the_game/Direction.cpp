#include "Direction.h"
#include <stdexcept>

Direction Direction::from(const Point& beg, const Point& end) throw() {
	if(beg.x() != end.x() && beg.y() != end.y()) {
		throw std::logic_error("Given points are not placed in line");
	}

	Point dir = end - beg;

	if(dir.x() != 0) {
		return dir.x() > 0 ? Direction::RIGHT : Direction::LEFT;
	}
	
	
	return dir.y() > 0 ? Direction::DOWN : Direction::UP;

}

Direction::Direction(const Dir& d) : m_direction(d) {

}

Direction::Dir Direction::get_dir() const {
	return m_direction;
}

Direction& Direction::operator=(const Dir& d) {
	m_direction = d;
	
	return *this;
}

Point Direction::to_point() const {
	switch (m_direction) {
	case UP:
		return Point(0, -1);
	case DOWN:
		return Point(0, 1);
	case LEFT:
		return Point(-1, 0);
	case RIGHT:
		return Point(1, 0);
	default:
		return Point(0, 0);
	}
}