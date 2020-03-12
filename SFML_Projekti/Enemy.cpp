#include "Enemy.h"
#include <iostream>
#include <math.h>

extern const int TILEMAPDIMENSIONS;

Enemy::Enemy(sf::Vector2f pos, BulletManager& bm, Tilemap& tilemap, std::string path)
	:
	Entity(pos,bm,tilemap,path)
{
	rect.setSize(sf::Vector2f(width, height));
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(pos);

	
	animations[int(AnimationIndex::RWALK)] = Animation(TextureManager::Get(), "textures/lunk.png", 0, 104 * 7, 10, 96, 104, 0.15f);
	animations[int(AnimationIndex::LWALK)] = Animation(TextureManager::Get(), "textures/lunk.png", 0, 104 * 5, 10, 96, 104, 0.15f);
	animations[int(AnimationIndex::UWALK)] = Animation(TextureManager::Get(), "textures/lunk.png", 0, 104 * 6, 10, 96, 104, 0.15f);
	animations[int(AnimationIndex::DWALK)] = Animation(TextureManager::Get(), "textures/lunk.png", 0, 104 * 4, 10, 96, 104, 0.15f);

	sprite.setScale({ 0.17f, 0.17f });
}

void Enemy::Update(sf::Vector2f mpos, std::vector<std::unique_ptr<Entity> >& em, Tilemap& tm, float dt)
{
	sf::Vector2f dir(0.f, 0.f);
	bool diagonalCheck[2] = { 0,0 };

	

	switch (state)
	{
	case Enemy::IDLE:
	{
		sf::CircleShape c(100.f);
		c.setPosition(GetPosCentered());
		if (CRCollision::CircleRectCollision(c, em[0]->GetRect()))
		{
			state = State::MOVING;
			aStar.Solve_AStar(GetPosInTilesCentered(), em[0]->GetPosInTilesCentered(), tm.GetCollisionLayer());
			pathVec = aStar.GetPathVector();
			std::reverse(pathVec.begin(), pathVec.end());
			aStarTarget.x = pathVec[pathIndex].x * TILEMAPDIMENSIONS;
			aStarTarget.y = pathVec[pathIndex].y * TILEMAPDIMENSIONS;
		}
	}
		break;

	case Enemy::MOVING:
	{
		UpdateAstar(GetPosInTilesCentered(), em[0]->GetPosInTilesCentered());
		const float xd = 1.f;
		// reitti
		float deltaX = pos.x - aStarTarget.x;
		float deltaY = pos.y - aStarTarget.y;
		if (deltaY < -xd)
		{
			// liiku alas
			dir += {0.0f, 1.0f};
			diagonalCheck[1] = 1;
			curAnimation = AnimationIndex::DWALK;
		}
		else if (deltaY > xd)
		{
			// liiku ylös
			dir += {0.0f, -1.0f};
			diagonalCheck[1] = 1;
			curAnimation = AnimationIndex::UWALK;
		}

		if (deltaX < -xd)
		{
			// liiku oikeelle
			dir += {1.0f, 0.0f};
			diagonalCheck[0] = 1;
			curAnimation = AnimationIndex::RWALK;
		}
		else if (deltaX > xd)
		{
			// liiku vas
			dir += {-1.0f, 0.0f};
			diagonalCheck[0] = 1;
			curAnimation = AnimationIndex::LWALK;
		}

		const int maali = std::sqrt((deltaX * deltaX) + (deltaY * deltaY));
		if (maali <= xd)
		{
			if (pathIndex < int(pathVec.size()) - 1)
			{
				//std::cout << (pathIndex - pathVec.size() - 1) << std::endl;
				pathIndex++;
				aStarTarget.x = pathVec[pathIndex].x * TILEMAPDIMENSIONS;
				aStarTarget.y = pathVec[pathIndex].y * TILEMAPDIMENSIONS;
			}
		}
		
	}
		break;
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
