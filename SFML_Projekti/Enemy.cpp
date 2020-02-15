#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos)
	:
	pos(pos)
{
	rect.setSize(sf::Vector2f(50, 50));
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(pos);
}

void Enemy::Update(float dt)
{
	if (hp <= 0)
	{
		dead = true;
	}
	// ehkä laittaa liikkuminen omaan funktioon ja sit se tähä
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

void Enemy::Draw(sf::RenderTarget& target)
{
	target.draw(rect);
}

sf::RectangleShape Enemy::GetRect()
{
	return rect;
}

void Enemy::OffsetHp(int offset)
{
	hp += offset;
}
