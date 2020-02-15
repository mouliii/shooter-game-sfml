#include "BulletManager.h"

void BulletManager::AddBullet(sf::Vector2f pos, sf::Vector2f dir, float radius, float speed, float maxDistance, sf::Color color)
{
	Bullet b(pos, dir, radius, speed, maxDistance, color);
	bulletArr.push_back(b);
}

void BulletManager::Update(float dt)
{
	for (size_t i = 0; i < bulletArr.size(); i++)
	{
		bulletArr[i].Update(dt);
		if (bulletArr[i].OverMaxDist())
		{
			bulletArr.erase(bulletArr.begin() + i);
		}
	}
}

void BulletManager::Draw(sf::RenderTarget& rt)
{
	for (size_t i = 0; i < bulletArr.size(); i++)
	{
		bulletArr[i].Draw(rt);
	}
}
