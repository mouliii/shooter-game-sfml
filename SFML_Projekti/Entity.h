#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "BulletManager.h"
#include "TextureManager.h"
#include "Animation.h"
#include "AStar.h"
#include "Weapon.h"


class Entity
{
public:
	Entity(sf::Vector2f pos, Tilemap& tilemap, std::string texture_path);
	virtual ~Entity();
	virtual void Update(sf::Vector2f mousepos, std::vector<std::unique_ptr<Entity> >& em, Tilemap& tm, float dt);
	void Draw(sf::RenderTarget& target);
	sf::RectangleShape& GetRect();
	virtual void GetDmg(int n) { hp -= n; }
	bool IsDead() { return isDead; }
	sf::Vector2f GetPos() { return pos; }
	sf::Vector2f GetPosCentered();
	virtual void Print() { std::cout << "entity debug print" << std::endl; }
	void SetPos(sf::Vector2f pos) { this->pos = pos; }
	void UpdateAstar(sf::Vector2i startPosCentered, sf::Vector2i endPosCentered);
	const sf::Vector2i GetPosInTilesCentered();
	bool LineofSight(sf::Vector2f origin, sf::Vector2f dest, int maxRange, int precision);
	void PickupWeapon(std::unique_ptr<Weapon> wep);
protected:
	// perus tiedot maailmasta
	Tilemap& tilemap;
	// entity specific jutut
	sf::Sprite sprite;
	sf::Vector2f pos;
	sf::RectangleShape rect;
	int hp = 3;
	float width = 16.f;
	float height = 16.f;
	bool isDead = false;
	float speed = 50.f;
	// ampuminen
	bool canShoot = true;
	float shootCooldown = 0.3f;
	float shootTimer = shootCooldown;
	// a star path finding
	Astar aStar;
	std::vector<sf::Vector2i> pathVec;
	int pathIndex = 0;
	sf::Vector2i aStarTarget = { 0.0f,0.0f };
	sf::Texture t;
	// TODO DEBUG
	std::unique_ptr<Weapon> weapon = nullptr;
};