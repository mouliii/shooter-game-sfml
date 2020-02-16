#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Bullet.h"


class BulletManager
{
public:
	BulletManager() = default;
	void AddBullet(sf::Vector2f pos, sf::Vector2f dir, float radius, float speed, float maxDistance, sf::Color color);
	void Update(float dt);
	void Draw(sf::RenderTarget& rt);
	std::vector<Bullet>& GetBullets() { return bulletArr; }
private:
	std::vector<Bullet> bulletArr;
};
