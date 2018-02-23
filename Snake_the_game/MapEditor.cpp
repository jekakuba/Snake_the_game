#include "MapEditor.h"
#include "Draw_config.h"
#include "Wall.h"
#include "Food.h"
#include "Portal.h"
#include "CircularSaw.h"
#include <iostream>

MapEditor::MapEditor(sf::RenderWindow & window, unsigned width, unsigned height)
	: Module(window, width, height), m_isMousePressing(false), m_brashObject(MapObject(0))
{
	updatePointingIcon();
}

void MapEditor::drawGrid()
{
	for (int i = 1; i < m_width; i++) {
		sf::RectangleShape rect(sf::Vector2f(1, DrawConfig::to_viewport_coord(m_height)));
		rect.setFillColor(DrawConfig::GRID_LINE_COLOR);
		rect.setPosition(sf::Vector2f(DrawConfig::to_viewport_coord(i), 0));
		m_window.draw(rect);
	}

	for (int i = 1; i < m_height; i++) {
		sf::RectangleShape rect(sf::Vector2f(DrawConfig::to_viewport_coord(m_width), 1));
		rect.setFillColor(DrawConfig::GRID_LINE_COLOR);
		rect.setPosition(sf::Vector2f(0, DrawConfig::to_viewport_coord(i)));
		m_window.draw(rect);
	}
}

void MapEditor::updatePointingIcon()
{
	Point mousePosition = DrawConfig::toPoint(sf::Mouse::getPosition(m_window));
	switch (m_brashObject)
	{
		case WALL: 
			m_selectedItem = std::move(std::unique_ptr<Wall>(new Wall(mousePosition)));
			break;
		case FOOD: 
			m_selectedItem = std::move(std::unique_ptr<Food>(new Food(mousePosition)));
			break;
		case PORTAL:
			m_selectedItem = std::move(std::unique_ptr<Portal>(new Portal(mousePosition)));
			break;
		case CIRCULAR_SAW:
			m_selectedItem = std::move(std::unique_ptr<CircularSaw>(new CircularSaw(mousePosition, mousePosition)));
			break;
	}
}

void MapEditor::draw()
{
	drawGrid();

	for (auto &stat : m_staticObjects) {
		stat.second->draw(m_window);
	}

	for (auto &dyn : m_dynamicObjects) {
		dyn.second->draw(m_window);
	}

	m_selectedItem->draw(m_window);
}

void MapEditor::update(const sf::Time & dt)
{
	for (auto &dyn : m_dynamicObjects) {
		dyn.second->update(dt);
	}
}

void MapEditor::handleInputEvent(sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		m_isMousePressing = true;
	}
	else if (event.type == sf::Event::MouseButtonReleased) {
		m_isMousePressing = false;
	}

	if (event.type == sf::Event::MouseWheelMoved)
	{
		int delta = event.mouseWheel.delta > 0 ? event.mouseWheel.delta : MAP_OBJECTS_AMOUNT + event.mouseWheel.delta;
		m_brashObject = MapObject(((int)m_brashObject + delta) % MAP_OBJECTS_AMOUNT);
	}
	updatePointingIcon();

	if (m_isMousePressing){
		Point clickPosition = DrawConfig::toPoint(sf::Mouse::getPosition(m_window));
		switch (m_brashObject)
		{
		case WALL:
			m_staticObjects[clickPosition] =  std::unique_ptr<Wall>(new Wall(clickPosition));
			break;
		case FOOD:
			m_staticObjects[clickPosition] = std::unique_ptr<Food>(new Food(clickPosition));
			break;
		case PORTAL:
			m_staticObjects[clickPosition] = std::unique_ptr<Portal>(new Portal(clickPosition));
			break;
		case CIRCULAR_SAW:
			break;
		}
	}
}
