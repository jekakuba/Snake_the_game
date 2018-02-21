#ifndef POINT_H
#define POINT_H

class Point {
public:
//  nullobject. Equals Point(INT_MAX, INT_MAX)
	static const Point NO_POINT;
public:
	explicit Point(int x = 0, int y = 0);
//  basic operations
	Point operator+(const Point& p) const;
	Point& operator+=(const Point& p);

	Point& operator-=(const Point& p);
	Point operator-(const Point& p) const;

	Point operator*(int i) const;
	Point& operator*=(int i);

	bool operator==(const Point& p) const;
	bool operator!=(const Point& p) const;

	//Returns point multiplied by -1
	Point reversed() const;

//  setters, getters
	void x(int x);
	void y(int y);

	int x() const;
	int y() const;

private:
	int m_x;
	int m_y;
};

#endif // POINT_H
