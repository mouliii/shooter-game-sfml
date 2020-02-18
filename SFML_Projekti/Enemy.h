#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"



class Enemy : public Entity
{
public:
	Enemy(sf::Vector2f pos, BulletManager* bm);
	virtual void Update(sf::Vector2f mpos, std::vector<Entity*> em, float dt) override;
	const int GetHp() { return hp; }
	void Print() override { std::cout << "vihu" << std::endl;}
private:
};
