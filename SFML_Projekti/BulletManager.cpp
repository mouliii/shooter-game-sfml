#include "BulletManager.h"
#include "EntityManager.h"
#include "RectCircleCollision.h"
#include <iostream>

void BulletManager::AddBullet(sf::Vector2f pos, sf::Vector2f dir, float radius, float speed, float maxDistance, sf::Color color, std::string owner)
{
	Bullet b(pos, dir, radius, speed, maxDistance, color, owner);
	bulletArr.push_back(b);
}

void BulletManager::Update( EntityManager* em, float dt)
{
	for (size_t i = 0; i < bulletArr.size(); i++)
	{
		// liikutetaan kaikki ammukset
		bulletArr[i].Update(dt);
		// check ettei oo liian pitkälle menny
		if (bulletArr[i].OverMaxDist())
		{
			bulletArr.erase(bulletArr.begin() + i);                ////// muista poistaa kun osuuu
			if (bulletArr.size() == 0)
			{
				break;
			}
		}
		// check collsion
		if (bulletArr[i].GetOwner() == "Player")
		{
			for (size_t j = 1; j < em->GetEntities().size(); j++)
			{
				if (CircleRectCollision(bulletArr[i].GetCircle(), em->GetEntities()[j]->GetRect()))
				{
					// TODO dmg source
					em->GetEntities()[j]->GetDmg(1);
					bulletArr.erase(bulletArr.begin() + i);
				}
			}
		}
		else if (bulletArr[i].GetOwner() == "Enemy")
		{
			if (CircleRectCollision(bulletArr[i].GetCircle(), em->GetEntities()[0]->GetRect()))
			{
				// TODO dmg source
				em->GetEntities()[0]->GetDmg(1);
				bulletArr.erase(bulletArr.begin() + i);
			}
		}
		else //  kaikki muut sekä "virheet"
		{

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
