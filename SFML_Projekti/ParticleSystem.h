#pragma once
#include <SFML/Graphics.hpp>
#include "Random.h"
#include <vector>


struct ParticleProperties
{
	sf::Vector2f vel = { 30.f,30.f };
	float sizeStart = 10.f;
	float sizeEnd = 1.f;
	float sizeVariation = 1.f;
	sf::Color startColor = sf::Color::Blue;
	sf::Color endColor = sf::Color::White;
	float lifeTime = 0.5f;
};


class ParticleSystem
{
public:
	void Draw(sf::RenderTarget& rt);
	void SpawnParticle(sf::Vector2f pos, const ParticleProperties& pp);
	void Update(float dt);
private:
	struct Particle
	{
		sf::Vector2f pos;
		sf::Vector2f vel;
		float sizeStart, sizeEnd;
		sf::Color startColor;
		sf::Color endColor;
		float rotation;
		float lifeTime;
		float fullLife;
	};
	bool backToFront = true;
	std::vector<Particle> particles;
};