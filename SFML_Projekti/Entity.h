#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "BulletManager.h"
#include "TextureManager.h"
#include "Animation.h"
#include <random>

extern const int TILEMAPDIMENSIONS;

class Entity
{
public:
	Entity(sf::Vector2f pos, BulletManager& bm, TextureManager& tm, Tilemap& tilemap, std::string path);
	virtual ~Entity();
	virtual void Update(sf::Vector2f mousepos, std::vector<std::unique_ptr<Entity> >& em, Tilemap& tm, float dt);
	void Draw(sf::RenderTarget& target);
	sf::RectangleShape& GetRect();
	virtual void GetDmg(int n) { hp -= n; }
	bool IsDead() { return isDead; }
	sf::Vector2f GetPos() { return pos; }
	sf::Vector2f GetPosCentered();
	const int GetRandomNumberInt(int min, int max);
	virtual void Print() { std::cout << "entity debug print" << std::endl; }
	void SetPos(sf::Vector2f pos) { this->pos = pos; }
	const sf::Vector2i GetPosInTiles() { return sf::Vector2i( (int(pos.x) + int(width) / 2) / TILEMAPDIMENSIONS, (int(pos.y) + int(height) / 2) / TILEMAPDIMENSIONS); }
protected:
	sf::Sprite sprite;
	int hp = 3;
	float width = 16.f;
	float height = 16.f;
	bool isDead = false;
	bool canShoot = true;
	float shootCooldown = 0.3f;
	float shootTimer = shootCooldown;
	float speed = 50.f;
	sf::Vector2i targetPos = {0.0f,0.0f};
	sf::Vector2f pos;
	sf::RectangleShape rect;
	//sf::Sprite sprite
	//sf::Texture texture;
	BulletManager& bm;
	TextureManager& tm;
	Tilemap& tilemap;
private:
	std::mt19937 rng{ std::random_device{} () };
};