#pragma once

#include <gtest\gtest.h>

#include <Direction.h>
#include <Direction.cpp>
TEST(Direction, ñonverting) {
	Direction d = Direction::RIGHT;
	d = Direction::UP;

	EXPECT_EQ(d.get_dir(), Direction::UP);
}

TEST(Direction, to_point) {
	Direction n = Direction::UP;
	Direction e = Direction::RIGHT;
	Direction w = Direction::LEFT;
	Direction s = Direction::DOWN;
	
	EXPECT_TRUE(n.to_point() == Point(0, -1));
	EXPECT_TRUE(e.to_point() == Point(1, 0));
	EXPECT_TRUE(w.to_point() == Point(-1, 0));
	EXPECT_TRUE(s.to_point() == Point(0, 1));
}