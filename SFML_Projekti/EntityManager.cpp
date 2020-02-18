#include "EntityManager.h"

void EntityManager::AddEntity(Entity& e)
{
	entities.push_back(&e);
}

void EntityManager::Update(sf::Vector2f mpos, std::vector<Entity*> em, float dt)
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->Update(mpos, em, dt);
		if (entities[i]->IsDead() )
		{
			entities.erase(entities.begin() + i);
		}
	}
}

void EntityManager::Draw(sf::RenderTarget& rt)
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->Draw(rt);
	}
}

std::vector<Entity*> EntityManager::GetEntities()
{
	std::vector<Entity*> tempVec;
	for (auto e : entities)
	{
		tempVec.push_back(e);
	}
	return tempVec;
}

