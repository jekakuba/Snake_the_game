#include "Map.h"
#include "Draw_config.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

int main() {
	Map game(32, 24);

	sf::RenderWindow window(sf::VideoMode(640, 480), "Snake game", sf::Style::Close);
	sf::Clock clock;

	window.setVerticalSyncEnabled(true);

	while (window.isOpen()) {
		sf::Event event;
		sf::Time dt = clock.restart();

		game.update(std::move(dt));

		while (window.pollEvent(event)) {
			
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed) {
				game.catchInput(event.key.code);
			}
		}

		window.clear(DrawConfig::BACKGROUND_COLOR);
		game.draw(window);
		window.display();
	}

	return 0;
}