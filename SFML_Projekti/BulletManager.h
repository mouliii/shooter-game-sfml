#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Bullet.h"


class BulletManager
{
public:
	BulletManager(const BulletManager&) = delete;
	static BulletManager& Get();
	static void AddBullet(sf::Vector2f pos, sf::Vector2f dir, float radius, float speed, float maxDistance, sf::Color color, std::string owner);
	static void Update(float dt);
	static void Draw(sf::RenderTarget& rt);
	static std::vector<std::unique_ptr<Bullet>>& GetBullets();
private:
	BulletManager() {};
	void I_AddBullet(sf::Vector2f pos, sf::Vector2f dir, float radius, float speed, float maxDistance, sf::Color color, std::string owner);
	void I_Update(float dt);
	void I_Draw(sf::RenderTarget& rt);
	std::vector<std::unique_ptr<Bullet>>& I_GetBullets() { return pBullets; }

	std::vector<std::unique_ptr<Bullet>> pBullets;
};
