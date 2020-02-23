#include "EntityManager.h"

void EntityManager::AddEntity(std::unique_ptr<Entity> e)
{
	pEntities.emplace_back(std::move(e));
}

void EntityManager::Update(sf::Vector2f mpos, float dt)
{
	for (size_t i = 0; i < pEntities.size(); i++)
	{
		pEntities[i]->Update(mpos, pEntities, dt);
		if (pEntities[i]->IsDead() )
		{
			pEntities.erase(pEntities.begin() + i);
		}
	}
}

void EntityManager::Draw(sf::RenderTarget& rt)
{
	for (size_t i = 0; i < pEntities.size(); i++)
	{
		pEntities[i]->Draw(rt);
	}
}

std::vector<std::unique_ptr<Entity>>& EntityManager::GetEntities()
{
	return pEntities;
}

