#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "EntityManager.h"
#include "Tilemap.h"
#include "BulletManager.h"
#include "RectCircleCollision.h"

class Collider
{
public:
	Collider() = default;
	void Move(sf::RectangleShape* body, sf::Vector2f delta);
	bool CheckCollision(sf::RectangleShape* _this, sf::IntRect* other);
	void Update(EntityManager* em, Tilemap& tm);
private:
};