#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "EntityManager.h"
#include "Tilemap.h"

class Collider
{
public:
	Collider() = default;
	void Move(sf::RectangleShape* body, sf::Vector2f delta);
	bool CheckCollision(sf::RectangleShape* _this, sf::IntRect* other);
	void Update(std::vector<std::unique_ptr<Entity>>& em, Tilemap& tm);
private:
};