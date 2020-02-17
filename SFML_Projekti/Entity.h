#pragma once
#include <SFML/Graphics.hpp>
#include "BulletManager.h"
#include <iostream>

class Entity
{
public:
	Entity(sf::Vector2f pos, BulletManager* bm);
	virtual void Update(sf::Vector2f mousepos, float dt);
	void Draw(sf::RenderTarget& target);
	sf::RectangleShape GetRect();
	void GetDmg(int n) { hp -= n; }
	bool IsDead() { return isDead; }
	virtual void Print() { std::cout << "entity debug print" << std::endl; }
protected:
	int hp = 3;
	bool isDead = false;
	float speed = 350.0f;
	sf::Vector2f pos;
	sf::RectangleShape rect;
	//sf::Sprite sprite
	//sf::Texture texture;
	BulletManager* bm;
};