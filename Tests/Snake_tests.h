#pragma once

#include <gtest\gtest.h>
#include <Snake.h>
#include <Snake.cpp>


TEST(Snake, Creation) {
	Snake snake(Point(3, 0), Direction::RIGHT, 3);
	Point expected[] = { Point(3,0), Point(2,0), Point(1,0) };

	int counter = 0;
	for (auto i : snake.body()) {
		EXPECT_EQ(i.x(), expected[counter].x());
		EXPECT_EQ(i.y(), expected[counter].y());
		++counter;
	}
}

TEST(Snake, Eating) {
	Snake snake(Point(3, 0), Direction::RIGHT, 3);
	
	snake.eat();
	EXPECT_EQ(snake.body().size(), 4);

	Point expected[] = { Point(3,0), Point(2,0), Point(1,0), Point(0,0) };
	
	int counter = 0;
	for (auto i : snake.body()) {
		EXPECT_EQ(i.x(), expected[counter].x());
		EXPECT_EQ(i.y(), expected[counter].y());
		++counter;
	}
}

TEST(Snake, change_direction) {
	Snake snake(Point(3, 0), Direction::RIGHT, 3);

	EXPECT_FALSE(snake.changeDir(Direction::LEFT));
	EXPECT_TRUE(snake.changeDir(Direction::DOWN));
}

TEST(Snake, Moving) {
	Snake snake(Point(3, 0), Direction::RIGHT, 4);

	snake.changeDir(Direction::DOWN);
	EXPECT_TRUE(snake.move());

	snake.changeDir(Direction::LEFT);
	EXPECT_TRUE(snake.move());

	snake.changeDir(Direction::UP);
	EXPECT_FALSE(snake.move());
}

TEST(Snake, Dissection) {
	Snake snake(Point(10, 0), Direction::RIGHT, 5);

	auto dissectPosition = --snake.body().end();
	auto cutPiece = snake.dissect(dissectPosition);

	EXPECT_EQ(snake.body().size(), 4);
	EXPECT_TRUE(cutPiece.empty());
	EXPECT_EQ(dissectPosition, snake.body().end());
}