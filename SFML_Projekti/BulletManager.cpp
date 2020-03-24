#include "BulletManager.h"

extern const int TILEMAPDIMENSIONS;

BulletManager& BulletManager::Get()
{
	static BulletManager instance;
	return instance;
}

void BulletManager::AddBullet(Type type, sf::Vector2f pos, sf::Vector2f dir, float radius, float speed, float maxDistance, sf::Color color, std::string owner)
{
	Get().I_AddBullet(type, pos, dir, radius, speed, maxDistance, color, owner);
}

void BulletManager::Update(float dt)
{
	Get().I_Update(dt);
}

void BulletManager::Draw(sf::RenderTarget& rt)
{
	Get().I_Draw(rt);
}

std::vector<std::unique_ptr<Bullet>>& BulletManager::GetBullets()
{
	return Get().I_GetBullets();
}

void BulletManager::I_AddBullet(Type type, sf::Vector2f pos, sf::Vector2f dir, float radius, float speed, float maxDistance, sf::Color color, std::string owner)
{
	if (type == Type::NORMAL)
	{
		auto b = std::make_unique<Bullet>(pos, dir, radius, speed, maxDistance, color, owner);
		pBullets.emplace_back(std::move(b));
	}
	else if (type == Type::SHELL)
	{
		for (size_t i = 0; i < 4; i++)
		{
			// TODO
			
			sf::Vector2f delta = dir - pos;
			const float length = std::sqrt((delta.x * delta.x) + (delta.y * delta.y));
			delta.x /= length;
			delta.y /= length;
			sf::Vector2f temp;
			temp.x = 30.f * delta.x + Random::GetRandomInt(-7, 7);
			temp.y = 30.f * delta.y + Random::GetRandomInt(-7, 7);
			temp += pos;
			pBullets.emplace_back(std::make_unique<Bullet>(pos, temp, radius, speed, maxDistance, color, owner));
			
		}
	}
}

void BulletManager::I_Update(float dt)
{
	for (size_t i = 0; i < pBullets.size(); i++)
	{
		// liikutetaan kaikki ammukset
		pBullets[i]->Update(dt);
		// check ettei oo liian pitkälle menny
		if (pBullets[i]->OverMaxDist())
		{
			pBullets.erase(pBullets.begin() + i);
			if (pBullets.size() == 0)
			{
				break;
			}
		}
	}
}

void BulletManager::I_Draw(sf::RenderTarget& rt)
{
	for (size_t i = 0; i < pBullets.size(); i++)
	{
		pBullets[i]->Draw(rt);
	}
}
