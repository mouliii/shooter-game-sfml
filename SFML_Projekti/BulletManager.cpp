#include "BulletManager.h"
#include "EntityManager.h"
#include "RectCircleCollision.h"
#include <iostream>

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

void BulletManager::Update( EntityManager* em, float dt)
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
		// check collsion
		if (pBullets[i]->GetOwner() == "Player")
		{
			for (size_t j = 1; j < em->GetEntities().size(); j++)
			{
				if (CircleRectCollision(pBullets[i]->GetCircle(), em->GetEntities()[j]->GetRect()))
				{
					// TODO dmg source
					em->GetEntities()[j]->GetDmg(1);
					pBullets.erase(pBullets.begin() + i);
				}
			}
		}
		else if (pBullets[i]->GetOwner() == "Enemy")
		{
			if (CircleRectCollision(pBullets[i]->GetCircle(), em->GetEntities()[0]->GetRect()))
			{
				// TODO dmg source
				em->GetEntities()[0]->GetDmg(1);
				pBullets.erase(pBullets.begin() + i);
			}
		}
		else //  kaikki muut sekä "virheet"
		{

		}
	}
	
	//////  bullet - wall collision /////////
	// TODO joteki smartimmaks ?

	for (size_t i = 0; i < pBullets.size(); i++)
	{
		int left = pBullets[i]->GetCircle().getPosition().x - pBullets[i]->GetCircle().getRadius();
		int top = pBullets[i]->GetCircle().getPosition().y - pBullets[i]->GetCircle().getRadius();
		int width = pBullets[i]->GetCircle().getPosition().x + pBullets[i]->GetCircle().getRadius();
		int height = pBullets[i]->GetCircle().getPosition().y + pBullets[i]->GetCircle().getRadius();

		for (int tempx = left ; tempx < width; tempx+= TILEMAPDIMENSIONS)
		{
			for (int tempy = top ; tempy < height; tempy+= TILEMAPDIMENSIONS)
			{
				if (tm.GetCollisionRect(tempx,tempy).second)
				{
					if (CircleRectCollision(pBullets[i]->GetCircle(), tm.GetCollisionRect(tempx,tempy).first))
					{
						//std::cout << pBullets.size() << std::endl;
						pBullets.erase(pBullets.begin() + i);
						break;
					}
				}
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
