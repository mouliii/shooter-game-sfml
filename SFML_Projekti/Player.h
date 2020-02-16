#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"



class Player : public Entity
{
public:
	Player(sf::Vector2f pos, BulletManager* bm);
	void Update(sf::Vector2f mousepos, float dt) override;
	virtual void Print() { std::cout << "playerin printti" << std::endl; }
private:
	// ampuminen
	bool canShoot = true;
	float shootCooldown = 0.3f;
	float shootTimer = shootCooldown;
};