#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Bullet
{
public:
	Bullet(sf::Vector2f pos, sf::Vector2f dir, float radius, float speed, float maxDistance, sf::Color color, std::string owner);
	void Update(float dt);
	void Draw(sf::RenderTarget& rt);
	bool OverMaxDist() { return pop; }
	sf::CircleShape GetCircle() { return cc; }
	std::string GetOwner() { return owner; }
private:
	std::string owner;
	sf::Vector2f pos;
	float radius;
	float speed;
	float maxDistance;
	sf::Vector2f dir;
	sf::CircleShape cc;
	sf::Color color;

	sf::Vector2f delta;
	float length;
	sf::Vector2f originalPos;

	bool pop = false;
};
