#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "RectCircleCollision.h"

class Event
{
public:
	Event(sf::RectangleShape eventRect)
		:
		rect(eventRect)
	{}
	virtual bool Check(sf::RectangleShape& _this)
	{
		std::cout << "event base Check --errorr--" << std::endl;
		return false;
	}
	virtual void Trigger(sf::RectangleShape& _this) {}
	const sf::RectangleShape GetRect() { return rect; }
protected:
	sf::RectangleShape rect;
};

class ChangeLevel : public Event
{
public:
	ChangeLevel(sf::RectangleShape eventRect)
		:
		Event(eventRect) {}

	bool Check(sf::RectangleShape& _this) override
	{
		if (_this.getGlobalBounds().intersects(rect.getGlobalBounds()) )
		{
			return true;
		}
		return false;
	}
	void Trigger(sf::RectangleShape& _this)
	{
		_this.setPosition(pos);
	}
private:
	sf::Vector2f pos = {5,102};
};

class SpawnMobs : public Event
{
public:
	SpawnMobs(sf::RectangleShape eventRect)
		:
		Event(eventRect) {}
private:
	int nMobs = 3;
};