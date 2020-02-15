#pragma once
#include "SFML/Graphics.hpp"



class Enemy
{
public:
	Enemy(sf::Vector2f pos);
	void Update(float dt);
	void Draw(sf::RenderTarget& target);
	sf::RectangleShape GetRect();
	void OffsetHp(int offset);
	const int GetHp() { return hp; }
private:
	bool dead = false;
	int hp = 3;
	float speed = 350.0f;
	sf::Vector2f pos;
	sf::RectangleShape rect;
	//sf::Sprite sprite
	//sf::Texture texture;
};