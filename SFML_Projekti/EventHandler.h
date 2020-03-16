#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tilemap.h"
#include "EntityManager.h"



class Event
{
public:
	Event();
	virtual void Check();
	virtual void Trigger();
private:
	bool triggered = false;
	std::string event_type;
	sf::IntRect rect;
};

class ChangeLevel : public Event
{
public:
	ChangeLevel();
private:
};

class SpawnMobs : public Event
{
public:
	SpawnMobs();
private:
	int nMobs;
};

// signelton
class EventHandler
{
public:
	void HandleEvents(Event* e);
private:
	std::vector<Event> events;
};