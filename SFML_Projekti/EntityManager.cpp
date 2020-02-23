#include "EntityManager.h"

void EntityManager::AddEntity(std::unique_ptr<Entity> e)
{
	entities.emplace_back(std::move(e));
}

void EntityManager::Update(sf::Vector2f mpos, float dt)
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->Update(mpos, entities, dt);
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

std::vector<std::unique_ptr<Entity>>& EntityManager::GetEntities()
{
	return entities;
}

