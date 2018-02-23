#include "Map.h"
#include "MapEditor.h"
#include "Draw_config.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

std::vector<std::unique_ptr<StaticObject>> generateLevel1(unsigned width, unsigned height) {
	std::vector<std::unique_ptr<StaticObject>> mo;
	
	for (int x = 0; x < width; ++x) {
		mo.push_back(std::unique_ptr<Wall>(new Wall(Point(x, 0))));
		mo.push_back(std::unique_ptr<Wall>(new Wall(Point(x, height - 1))));
	}
	
	for (int y = 0; y < height; ++y) {
		mo.push_back(std::unique_ptr<Wall>(new Wall(Point(0, y))));
		mo.push_back(std::unique_ptr<Wall>(new Wall(Point(width - 1, y))));
	}
	
	std::unique_ptr<Portal> p1(new Portal(Point(11, 5)));
	std::unique_ptr<Portal> p2(new Portal(Point(width-5, height-5)));
	
	p1->connectWith(*p2);
	mo.push_back(std::move(p1));
	mo.push_back(std::move(p2));

	Point mapCenter = Point((width - 2) / 2, (height - 2) / 2);
		
	for (int x = mapCenter.x() - 8; x <= mapCenter.x() + 8; ++x) {
		mo.push_back(std::unique_ptr<Wall>(new Wall(Point(x, mapCenter.y()))));
	}
	
	for (int y = mapCenter.y() - 4; y <= mapCenter.y() + 4; ++y) {
		mo.push_back(std::unique_ptr<Wall>(new Wall(Point(mapCenter.x(), y))));
	}

	return mo;
}

std::vector<std::unique_ptr<DynamicObject>> generateDynObjectsLevel1() {
	std::vector<std::unique_ptr<DynamicObject>> ret;

	ret.push_back(std::unique_ptr<CircularSaw>(new CircularSaw(Point(10, 1), Point(10, 10), sf::milliseconds(100))));
	ret.push_back(std::unique_ptr<CircularSaw>(new CircularSaw(Point(13, 1), Point(13, 10), sf::milliseconds(75))));
	ret.push_back(std::unique_ptr<CircularSaw>(new CircularSaw(Point(16, 1), Point(16, 10), sf::milliseconds(66))));
	ret.push_back(std::unique_ptr<CircularSaw>(new CircularSaw(Point(19, 1), Point(19, 10), sf::milliseconds(150))));

	return ret;
}

int main() {
	
	sf::RenderWindow window(sf::VideoMode(640, 480), "Snake game", sf::Style::Close);
	sf::Clock clock;

	//std::unique_ptr<Module> module(new Map(window, 32, 24, generateLevel1(32, 24), generateDynObjectsLevel1()));
	std::unique_ptr<Module> module(new MapEditor(window, 32, 24));

	window.setVerticalSyncEnabled(true);

	while (window.isOpen()) {
		sf::Event event;
		sf::Time dt = clock.restart();

		module->update(std::move(dt));

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			module->handleInputEvent(event);
		}

		window.clear(DrawConfig::BACKGROUND_COLOR);
		module->draw();
		window.display();
	}

	return 0;
}