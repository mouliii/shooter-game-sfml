#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"



class Enemy : public Entity
{
public:
	Enemy(sf::Vector2f pos, BulletManager* bm);
	virtual void Update(sf::Vector2f mpos, float dt) override;
	void OffsetHp(int offset);
	const int GetHp() { return hp; }
	void Print() override { std::cout << "vihu" << std::endl;}
private:
	bool dead = false;
	int hp = 3;
};