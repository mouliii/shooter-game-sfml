#include "Enemy.h"
#include <iostream>
#include "RectCircleCollision.cpp"

Enemy::Enemy(sf::Vector2f pos, BulletManager& bm, TextureManager& tm, std::string path)
	:
	Entity(pos,bm,tm,path)
{
	rect.setSize(sf::Vector2f(width, height));
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(pos);

	animations[int(AnimationIndex::RWALK)] = Animation(tm, "textures/lunk.png", 0, 104 * 7, 10, 96, 104, 0.15f);
	animations[int(AnimationIndex::LWALK)] = Animation(tm, "textures/lunk.png", 0, 104 * 5, 10, 96, 104, 0.15f);
	animations[int(AnimationIndex::UWALK)] = Animation(tm, "textures/lunk.png", 0, 104 * 6, 10, 96, 104, 0.15f);
	animations[int(AnimationIndex::DWALK)] = Animation(tm, "textures/lunk.png", 0, 104 * 4, 10, 96, 104, 0.15f);

	sprite.setScale({ 0.17f, 0.17f });
}

void Enemy::Update(sf::Vector2f mpos, std::vector<std::unique_ptr<Entity> >& em, float dt)
{
	switch (state)
	{
	case Enemy::IDLE:
	{
		sf::CircleShape c(20.f);
		c.setPosition(GetPosCentered() );
		if (CircleRect::CircleRectCollision(c,em[0]->GetRect()) )
		{
			state = State::AGGROED;
		}
	}
		animations[curAnimation].StopAnimation();
		animations[curAnimation].SetFrameTo(4);
		animations[curAnimation].ApplyToSprite(sprite);
	case Enemy::WANDERING:
		break;
	case Enemy::AGGROED:
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
		break;
	default:
		break;
	}
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
}
