#include "Player.h"

Player::Player(sf::Vector2f pos, Tilemap& tilemap, std::string path)
	:
	Entity(pos, tilemap, path)
{
	rect.setSize({ width,height });
	//rect.setFillColor(sf::Color::Blue);
	rect.setPosition(pos);
	sprite.setScale({ 0.17f, 0.17f });

	animations[int(AnimationIndex::RWALK)] = Animation(TextureManager::Get(), "textures/lunk.png", 0, 104 * 7, 10, 96, 104, 0.15f);
	animations[int(AnimationIndex::LWALK)] = Animation(TextureManager::Get(), "textures/lunk.png", 0, 104 * 5, 10, 96, 104, 0.15f);
	animations[int(AnimationIndex::UWALK)] = Animation(TextureManager::Get(), "textures/lunk.png", 0, 104 * 6, 10, 96, 104, 0.15f);
	animations[int(AnimationIndex::DWALK)] = Animation(TextureManager::Get(), "textures/lunk.png", 0, 104 * 4, 10, 96, 104, 0.15f);

	weapon = std::make_unique<Shotgun>(GetPosCentered(), "textures/Weapons/shotgun.png");
	reloadTimer = weapon->GetReloadTime();

	id = "Player";
	hp = 8;
	sf::SoundBuffer sb;
	sb.loadFromFile("Sounds/Gun/Pistol/Shot.wav");
	pum.second = std::move(sb);
	pum.first.setBuffer(pum.second);
	pum.first.setVolume(15.f);
	//reload sound
	sb.loadFromFile("Sounds/Gun/Pistol/Reload.wav");
	s_reload.second = std::move(sb);
	s_reload.first.setBuffer(s_reload.second);
	s_reload.first.setVolume(40.f);
}

void Player::Update(sf::Vector2f mousepos, std::vector<std::unique_ptr<Entity> >& em, Tilemap& tm, float dt)
{
	// update liikkuminen ja animaatio
	UpdateMovement(mousepos, dt);
	if (weapon != nullptr)
	{
		if (mousepos.x < GetPosCentered().x)
		{
			weapon->UpdatePos({ GetPosCentered().x, GetPosCentered().y }, mousepos);
		}
		else
		{
			weapon->UpdatePos({ GetPosCentered().x, GetPosCentered().y }, mousepos);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			reload = true;
		}
		// update ampuminen
		if (!reload)
		{
			if (canShoot)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					pum.first.play();
					canShoot = false;
					BulletManager::AddBullet(weapon->GetType(), GetPosCentered(), mousepos, 3.5f, 200.f, 400.f, sf::Color::Green, id);
					weapon->ReduceCurAmmo(1);
					if (weapon->GetCurBullets() <= 0)
					{
						reload = true;
					}
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
		else
		{
			reloadTimer -= dt;
			if (reloadTimer <= 0.0f)
			{
				s_reload.first.play();
				reloadTimer = weapon->GetReloadTime();
				weapon->Reload();
				reload = false;
			}
		}
		
	}
	
	if (!canTakeDmg)
	{
		invisTimer -= dt;
		if (invisTimer <= 0.0f)
		{
			std::cout << hp << std::endl;
			canTakeDmg = true;
			invisTimer = 0.5f;
		}
	}
	if (hp <= 0)
	{
		std::cout << "DETH" << std::endl;
	}
}

void Player::UpdateMovement(sf::Vector2f mousepos, float dt)
{
	// ehk� laittaa liikkuminen omaan funktioon ja sit se t�h�
	sf::Vector2f dir(0.f, 0.f);
	bool diagonalCheck[2] = { 0,0 };

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
	rect.move(dir.x * spd, dir.y * spd);
	sprite.setPosition(rect.getPosition());
	pos = rect.getPosition();

	// animaatio
	sf::Vector2f delta = GetPosCentered() - mousepos;
	float rotation = atan2(delta.y, delta.x) * 180 / 3.14159265f;
	if (rotation > -45 && rotation < 45)
	{
		// vasen
		curAnimation = AnimationIndex::LWALK;
	}
	else if (rotation > 45 && rotation < 135)
	{
		// yl�
		curAnimation = AnimationIndex::UWALK;
	}
	else if (rotation < -45 && rotation > -135 )
	{
		// ala
		curAnimation = AnimationIndex::DWALK;
	}
	else if (rotation > 135 || rotation < -135)
	{
		// oikea
		curAnimation = AnimationIndex::RWALK;
	}
	// animaation pys�ytys
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
	animations[curAnimation].Update(dt);
	animations[curAnimation].ApplyToSprite(sprite);
}
