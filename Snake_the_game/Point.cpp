#include "Point.h"

#include <limits.h>

const Point Point::NO_POINT = Point(INT_MAX, INT_MAX);

Point::Point(int x, int y) : m_x(x), m_y(y) {}

Point Point::operator+(const Point& p) const {
	return Point(m_x + p.m_x, m_y + p.m_y);
}

Point& Point::operator+=(const Point& p) {
	m_x += p.x();
	m_y += p.y();
	return *this;
}

Point& Point::operator-=(const Point& p) {
	m_x -= p.x();
	m_y -= p.y();
	return *this;
}

Point Point::operator-(const Point& p) const{
	return Point(m_x - p.m_x, m_y - p.m_y);
}

Point Point::operator*(int i) const {
	return Point(m_x * i, m_y * i);
}

Point& Point::operator*=(int i) {
	m_x *= i;
	m_y *= i;
	return *this;
}

Point Point::reversed() const {
	return Point(m_x * -1, m_y * -1);
}

void Point::x(int i) {
	m_x = i;
}

void Point::y(int i) {
	m_y = i;
}

bool Point::operator==(const Point& p) const {
	return m_x == p.m_x && m_y == p.m_y;
}

bool Point::operator!=(const Point& p) const {
	return !(*this == p);
}

int Point::x() const {
	return m_x;
}

int Point::y() const {
	return m_y;
}
