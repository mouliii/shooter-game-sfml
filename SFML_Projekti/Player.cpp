#include "Player.h"

Player::Player(sf::Vector2f pos, BulletManager* bm)
	:
	Entity(pos,bm)
{
	rect.setSize(sf::Vector2f(50, 50));
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(5);
	rect.setPosition(pos);
}

void Player::Update(sf::Vector2f mousepos, std::vector<Entity*> em, float dt)
{
	// ehkä laittaa liikkuminen omaan funktioon ja sit se tähä
	sf::Vector2f dir(0.f,0.f);
	bool diagonalCheck[2] = { 0,0 };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		dir += { -1.f, 0.f };
		diagonalCheck[0] = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dir += { 1.f, 0.f };
		diagonalCheck[0] = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		dir += { 0.f, -1.f };
		diagonalCheck[1] = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		dir += { 0.f, 1.f };
		diagonalCheck[1] = 1;
	}
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

	rect.setPosition( pos );
	// update ampuminen
	if (canShoot)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			canShoot = false;
			bm->AddBullet(rect.getPosition(), mousepos, 10.f, 450.f, 400.f, sf::Color::Green,"Player");
		}
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