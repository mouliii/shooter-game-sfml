#include "BulletManager.h"

extern const int TILEMAPDIMENSIONS;

BulletManager::BulletManager(Tilemap& tm)
	:
	tm(tm)
{
}

void BulletManager::AddBullet(sf::Vector2f pos, sf::Vector2f dir, float radius, float speed, float maxDistance, sf::Color color, std::string owner)
{
	std::unique_ptr<Bullet> b(new Bullet(pos, dir, radius, speed, maxDistance, color, owner));
	pBullets.emplace_back(std::move(b) );
}

void BulletManager::Update(float dt)
{
	for (size_t i = 0; i < pBullets.size(); i++)
	{
		// liikutetaan kaikki ammukset
		pBullets[i]->Update(dt);
		// check ettei oo liian pitkälle menny
		if (pBullets[i]->OverMaxDist())
		{
			pBullets.erase(pBullets.begin() + i);                ////// muista poistaa kun osuuu
			if (pBullets.size() == 0)
			{
				break;
			}
		}
	}
}

void BulletManager::Draw(sf::RenderTarget& rt)
{
	for (size_t i = 0; i < pBullets.size(); i++)
	{
		pBullets[i]->Draw(rt);
	}
}
