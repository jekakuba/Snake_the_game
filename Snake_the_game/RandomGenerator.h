#pragma once

#include "Point.h"
#include <random>

class RandomGenerator {
public:
	RandomGenerator();
	//generates random point in rectangle defined by
	//lower_bound(inclusive) and upper_bound(exclusive)
	Point generatePoint(Point&& lower_bound, Point&& upper_bound);
private:
	std::random_device m_randomDevice;
	std::mt19937 m_randomEngine;
};

