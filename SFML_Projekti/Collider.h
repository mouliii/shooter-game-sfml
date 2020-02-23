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
	void CheckCollision(sf::RectangleShape* _this, sf::RectangleShape* other,  float push);
	void Update(std::vector<Entity*> e, std::vector<Tile*> t);
private:
};