#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "BulletManager.h"



class Player
{
public:
	Player(sf::Vector2f pos, BulletManager* bm);
	void Update(sf::Vector2f mousepos, float dt);
	void Draw(sf::RenderTarget& target);
	sf::RectangleShape GetRect();
private:
	float speed = 350.0f;
	sf::Vector2f pos;
	sf::RectangleShape rect;
	//sf::Sprite sprite
	//sf::Texture texture;
	// ampuminen
	bool canShoot = true;
	float shootCooldown = 0.3f;
	float shootTimer = shootCooldown;
	BulletManager* bm;
};