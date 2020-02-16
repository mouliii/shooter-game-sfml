#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

class EntityManager
{
public:
	EntityManager() = default;
	~EntityManager() { }
	void AddEntity(Entity& e)
	{
		entities.push_back(&e);
	}
	void Update(sf::Vector2f mpos, float dt)
	{
		for (size_t i = 0; i < entities.size(); i++)
		{
			entities[i]->Update(mpos,dt);
		}
	}
	void Draw(sf::RenderTarget& rt)
	{
		for (size_t i = 0; i < entities.size(); i++)
		{
			entities[i]->Draw(rt);
		}
	}
	size_t GetArraySize() { return entities.size(); }
	//std::vector<Entity>& GetEntities() { return &entities; }
private:
	std::vector<Entity*> entities;
};