#include "Enemy.h"
#include <iostream>

Enemy::Enemy(sf::Vector2f pos, BulletManager& bm, TextureManager& tm, std::string path)
	:
	Entity(pos,bm,tm,path)
{
	rect.setSize(sf::Vector2f(width, height));
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(pos);


	sprite.setScale({ 0.2f, 0.2f });
	sprite.setTextureRect(sf::IntRect(100, 100, 100, 200));
}

void Enemy::Update(sf::Vector2f mpos, std::vector<std::unique_ptr<Entity> >& em, float dt)
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

	sprite.move(dir.x * spd, dir.y * spd);
	pos = sprite.getPosition();

	// ampuminen
	if (canShoot)
	{
		canShoot = false;
		bm.AddBullet(GetPosCentered(), em[0]->GetPosCentered(), 5.f, 300.f, 250.f, sf::Color::Green, "Enemy");
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
