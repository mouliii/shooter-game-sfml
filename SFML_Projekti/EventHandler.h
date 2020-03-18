#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Event.h"



// signelton
class EventHandler
{
public:
	EventHandler(const EventHandler&) = delete;
	static EventHandler& Get();
	static void HandleEvents(sf::RectangleShape& _this);
	static void AddEvent(std::unique_ptr<Event> e);
	static void GetEvents();
private:
	EventHandler() {};
	void I_HandleEvents(sf::RectangleShape& _this);
	void I_AddEvent(std::unique_ptr<Event> e);
	std::vector<std::unique_ptr<Event>>& I_GetEvents() { return events; }
	std::vector<std::unique_ptr<Event>> events;
};