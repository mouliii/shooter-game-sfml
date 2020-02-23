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
	void AddEntity(std::unique_ptr<Entity> e);
	void Update(sf::Vector2f mpos, float dt);
	void Draw(sf::RenderTarget& rt);
	size_t GetArraySize() { return pEntities.size(); }
	std::vector<std::unique_ptr<Entity>>& GetEntities();
private:
	std::vector<std::unique_ptr<Entity> > pEntities;
};