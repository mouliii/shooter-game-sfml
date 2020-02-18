#include "Enemy.h"
#include <iostream>

Enemy::Enemy(sf::Vector2f pos, BulletManager* bm)
	:
	Entity(pos,bm)
{
	rect.setSize(sf::Vector2f(50, 50));
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(pos);
}

void Enemy::Update(sf::Vector2f mpos, std::vector<Entity*> em, float dt)
{
	// dead check
	if (hp <= 0)
	{
		isDead = true;
	}
	// liikkuminen - target
	sf::Vector2f dir(0.f, 0.f);
	bool diagonalCheck[2] = { 0,0 };
	float spd = 0.0f;
	if (diagonalCheck[0] && diagonalCheck[1])
	{
		spd = speed * dt * 0.707f;
	}
	else
	{
		spd = speed * dt;
	}
	pos.x += dir.x * spd;
	pos.y += dir.y * spd;
	rect.setPosition(pos);
	// ampuminen
	if (canShoot)
	{
		canShoot = false;
		bm->AddBullet(rect.getPosition(), em[0]->GetRect().getPosition(), 10.f, 450.f, 250.f, sf::Color::Green, "Enemy");
	}
	else
	{
		shootTimer -= dt;
		if (shootTimer <= 0.0f)
		{
			canShoot = true;
			shootTimer = shootCooldown;
		}
	}
}
