#pragma once

#include <gtest\gtest.h>
#include <Point.h>
#include <Point.cpp>

TEST(Point, Add) {
	Point p1(1, 0);
	Point p2(0, 1);

	Point p = p1 + p2;

	EXPECT_EQ(p.x(), 1);
	EXPECT_EQ(p.y(), 1);

	p += p;

	EXPECT_EQ(p.x(), 2);
	EXPECT_EQ(p.y(), 2);
}

TEST(Point, Sub) {
	Point p1(-1, 0);
	Point p2(0, 1);

	Point p = p1 - p2;

	EXPECT_EQ(p.x(), -1);
	EXPECT_EQ(p.y(), -1);

	p -= p;

	EXPECT_EQ(p.x(), 0);
	EXPECT_EQ(p.y(), 0);
}

TEST(Point, Mul) {
	Point p(2, 2);

	p = p * 2;

	EXPECT_EQ(p.x(), 4);
	EXPECT_EQ(p.y(), 4);

	p *= 2;

	EXPECT_EQ(p.x(), 8);
	EXPECT_EQ(p.y(), 8);
}

TEST(Point, Reversed) {
	Point p(1, 0);

	p = p.reversed();

	EXPECT_EQ(p.x(), -1);
	EXPECT_EQ(p.y(), 0);
}

TEST(Point, Set_Get) {
	Point p(1, 0);
	p.x(2); p.y(3);

	EXPECT_EQ(p.x(), 2);
	EXPECT_EQ(p.y(), 3);
}

TEST(Point, Equality) {
	Point p1(2, 3);
	Point p2(2, 3);

	EXPECT_TRUE(p1 == p2);
	EXPECT_FALSE(p1 != p2);

	p1.x(6);

	EXPECT_FALSE(p1 == p2);
	EXPECT_TRUE(p1 != p2);
}