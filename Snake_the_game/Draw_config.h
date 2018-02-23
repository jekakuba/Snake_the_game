#pragma once
#include <SFML\Graphics.hpp>
//Stores information about how to draw the game

namespace DrawConfig {
	//one cell size in px
	//should be a multiple of width and height of the window
	constexpr int SCALE = 20; 

	const sf::Color SNAKE_COLOR = sf::Color(0, 150, 0);
	const sf::Color BACKGROUND_COLOR = sf::Color(120, 255, 120);
	const sf::Color FOOD_COLOR = sf::Color(255, 0, 0, 255);
	const sf::Color WALL_COLOR = sf::Color(90, 90, 90, 255);
	const sf::Color PORTAL_COLOR = sf::Color::Blue;
	const sf::Color SAW_COLOR = sf::Color::White;
	const sf::Color SAW_PATH_COLOR = sf::Color::Black;
	const sf::Color GRID_LINE_COLOR = sf::Color::Red;

	inline int to_viewport_coord(int c) { return c * SCALE; }
	inline int from_viewport_coord(int c) { return c / SCALE; }
	inline Point toPoint(const sf::Vector2i& v) { return Point(v.x / SCALE, v.y / SCALE); }
}