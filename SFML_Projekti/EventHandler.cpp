#include "EventHandler.h"

EventHandler& EventHandler::Get()
{
	static EventHandler instance;
	return instance;
}

void EventHandler::HandleEvents(sf::RectangleShape& t)
{
	Get().I_HandleEvents(t);
}

void EventHandler::AddEvent(std::unique_ptr<Event> e)
{
	Get().I_GetEvents().emplace_back(std::move(e));
}

void EventHandler::GetEvents()
{
	Get().I_GetEvents();
}

void EventHandler::I_HandleEvents(sf::RectangleShape& t)
{
	for (size_t i = 0; i < events.size(); i++)
	{
		if (events[i]->Check(t))
		{
			events[i]->Trigger(t);
		}
	}
}

void EventHandler::I_AddEvent(std::unique_ptr<Event> e)
{
	events.emplace_back(std::move(e));
}
