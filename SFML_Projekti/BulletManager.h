#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Tilemap.h"


class BulletManager
{
public:
	BulletManager(Tilemap& tm);
	void AddBullet(sf::Vector2f pos, sf::Vector2f dir, float radius, float speed, float maxDistance, sf::Color color, std::string owner);
	void Update(class EntityManager* em,float dt);
	void Draw(sf::RenderTarget& rt);
	std::vector<std::unique_ptr<Bullet>>& GetBullets() { return pBullets; }
private:
	std::vector<std::unique_ptr<Bullet>> pBullets;
	Tilemap& tm;
};
