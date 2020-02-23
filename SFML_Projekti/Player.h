#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"



class Player : public Entity
{
public:
	Player(sf::Vector2f pos, BulletManager* bm);
	void Update(sf::Vector2f mousepos, std::vector<std::unique_ptr<Entity> >& em, float dt) override;
	virtual void Print() { std::cout << "playerin printti" << std::endl; }
private:
	float speed = 100.f;
};