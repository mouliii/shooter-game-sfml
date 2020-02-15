#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "Bullet.h"



class Player
{
public:
	Player(sf::Vector2f pos);
	void Update(sf::Vector2f mousepos, float dt);
	void Draw(sf::RenderTarget& target);
	sf::RectangleShape GetRect();
	std::vector<Bullet> GetBullets() { return bulletArr; }
	void PopBullet(int i) { bulletArr.erase(bulletArr.begin() + i); }
private:
	float speed = 350.0f;
	sf::Vector2f pos;
	sf::RectangleShape rect;
	std::vector<Bullet> bulletArr;
	//sf::Sprite sprite
	//sf::Texture texture;
	// ampuminen
	bool canShoot = true;
	float shootCooldown = 0.3f;
	float shootTimer = shootCooldown;
};