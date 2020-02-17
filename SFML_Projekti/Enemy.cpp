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

void Enemy::Update(sf::Vector2f mpos, float dt)
{
	if (hp <= 0)
	{
		isDead = true;
	}
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
}
