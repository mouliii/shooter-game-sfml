#include "BulletManager.h"

extern const int TILEMAPDIMENSIONS;

BulletManager& BulletManager::Get()
{
	static BulletManager instance;
	return instance;
}

void BulletManager::AddBullet(sf::Vector2f pos, sf::Vector2f dir, float radius, float speed, float maxDistance, sf::Color color, std::string owner)
{
	Get().I_AddBullet(pos, dir, radius, speed, maxDistance, color, owner);
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

void BulletManager::I_AddBullet(sf::Vector2f pos, sf::Vector2f dir, float radius, float speed, float maxDistance, sf::Color color, std::string owner)
{
	std::unique_ptr<Bullet> b(new Bullet(pos, dir, radius, speed, maxDistance, color, owner));
	pBullets.emplace_back(std::move(b));
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
