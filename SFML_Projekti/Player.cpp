#include "Player.h"

Player::Player(sf::Vector2f pos, BulletManager& bm, TextureManager& tm, std::string path)
	:
	Entity(pos, bm, tm, path)
{
	rect.setSize({ width,height });
	//rect.setFillColor(sf::Color::Blue);
	rect.setPosition(pos);
	sprite.setScale({ 0.17f, 0.17f });

	animations[int(AnimationIndex::RWALK)] = Animation(tm, "textures/lunk.png", 0, 104 * 7, 10, 96, 104, 0.15f);
	animations[int(AnimationIndex::LWALK)] = Animation(tm, "textures/lunk.png", 0, 104 * 5, 10, 96, 104, 0.15f);
	animations[int(AnimationIndex::UWALK)] = Animation(tm, "textures/lunk.png", 0, 104 * 6, 10, 96, 104, 0.15f);
	animations[int(AnimationIndex::DWALK)] = Animation(tm, "textures/lunk.png", 0, 104 * 4, 10, 96, 104, 0.15f);
}

void Player::Update(sf::Vector2f mousepos, std::vector<std::unique_ptr<Entity> >& em, float dt)
{
	// update liikkuminen ja animaatio
	UpdateMovement(mousepos, dt);
	// update ampuminen
	if (canShoot)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			canShoot = false;
			bm.AddBullet(GetPosCentered(), mousepos, 5.f, 400.f, 400.f, sf::Color::Green,"Player");
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

void Player::UpdateMovement(sf::Vector2f mousepos, float dt)
{
	// ehkä laittaa liikkuminen omaan funktioon ja sit se tähä
	sf::Vector2f dir(0.f, 0.f);
	bool diagonalCheck[2] = { 0,0 };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		dir += { 0.f, -1.f };
		diagonalCheck[1] = 1;
		curAnimation = AnimationIndex::UWALK;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		dir += { 0.f, 1.f };
		diagonalCheck[1] = 1;
		curAnimation = AnimationIndex::DWALK;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		dir += { -1.f, 0.f };
		diagonalCheck[0] = 1;
		curAnimation = AnimationIndex::LWALK;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dir += { 1.f, 0.f };
		diagonalCheck[0] = 1;
		curAnimation = AnimationIndex::RWALK;
	}
	float spd = 0.0f;
	if (diagonalCheck[0] && diagonalCheck[1])
	{
		spd = speed * dt * 0.707f;
		animations[curAnimation].ResumeAnimation();
	}
	else
	{
		spd = speed * dt;
		animations[curAnimation].ResumeAnimation();
	}
	if (!diagonalCheck[0] && !diagonalCheck[1])
	{
		animations[curAnimation].StopAnimation();
		if (int(curAnimation) == 1)
		{
			animations[curAnimation].SetFrameTo(4);
		}
		else
		{
			animations[curAnimation].SetFrameTo(0);
		}
	}
	rect.move(dir.x * spd, dir.y * spd);
	sprite.setPosition(rect.getPosition());
	pos = rect.getPosition();
	animations[curAnimation].Update(dt);
	animations[curAnimation].ApplyToSprite(sprite);
}
