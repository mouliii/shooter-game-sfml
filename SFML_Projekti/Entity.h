#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "BulletManager.h"
#include "TextureManager.h"
#include "Animation.h"

class Entity
{
public:
	Entity(sf::Vector2f pos, BulletManager& bm, TextureManager& tm, std::string path);
	virtual ~Entity();
	virtual void Update(sf::Vector2f mousepos, std::vector<std::unique_ptr<Entity> >& em, float dt);
	void Draw(sf::RenderTarget& target);
	sf::RectangleShape& GetRect();
	virtual void GetDmg(int n) { hp -= n; }
	bool IsDead() { return isDead; }
	sf::Vector2f GetPos() { return pos; }
	sf::Vector2f GetPosCentered();
	virtual void Print() { std::cout << "entity debug print" << std::endl; }
	void SetPos(sf::Vector2f pos) { this->pos = pos; }
protected:
	sf::Sprite sprite;
	int hp = 3;
	float width = 16.f;
	float height = 16.f;
	bool isDead = false;
	bool canShoot = true;
	float shootCooldown = 0.3f;
	float shootTimer = shootCooldown;
	float speed = 350.0f;
	sf::Vector2f pos;
	sf::RectangleShape rect;
	//sf::Sprite sprite
	//sf::Texture texture;
	BulletManager& bm;
	TextureManager& tm;
};