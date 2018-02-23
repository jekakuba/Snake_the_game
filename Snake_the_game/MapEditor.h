#pragma once
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include <memory>
#include <map>

#include "Module.h"
#include "StaticObject.h"
#include "DynamicObject.h"

#define MAP_OBJECTS_AMOUNT 4

class MapEditor: public Module
{
public:
	enum MapObject { WALL, FOOD, PORTAL, CIRCULAR_SAW };
	MapEditor(sf::RenderWindow& window, unsigned width, unsigned height);
	void drawGrid();
	void updatePointingIcon();
public: //Module abstract class implementation
	virtual void draw() override;
	virtual void update(const sf::Time &) override;
	virtual void handleInputEvent(sf::Event&) override;
private: 
	bool m_isMousePressing;
	MapObject m_brashObject;
	std::unique_ptr<StaticObject> m_selectedItem;
	std::map <Point, std::unique_ptr<StaticObject>> m_staticObjects;
	std::map <Point, std::unique_ptr<DynamicObject>> m_dynamicObjects;
};

