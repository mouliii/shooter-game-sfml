#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Collider.h"

class EntityManager
{
public:
	EntityManager() = default;
	~EntityManager() { }
	void AddEntity(Entity& e);
	void Update(sf::Vector2f mpos, std::vector<Entity*> em, float dt);
	void Draw(sf::RenderTarget& rt); 
	std::vector<Entity*> GetEntities();
private:
	std::vector<Entity*> entities;
};