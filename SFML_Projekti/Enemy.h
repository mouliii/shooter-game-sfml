#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"



class Enemy : public Entity
{
private:
	enum AnimationIndex
	{
		LWALK,
		RWALK,
		UWALK,
		DWALK,
		COUNT
	};
	enum State
	{
		IDLE,
		WANDERING,
		AGGROED
	};
public:
	Enemy(sf::Vector2f pos, BulletManager& bm, TextureManager& tm, std::string path);
	virtual void Update(sf::Vector2f mpos, std::vector<std::unique_ptr<Entity>>& em, float dt) override;
	const int GetHp() { return hp; }
	void Print() override { std::cout << "vihu" << std::endl;}
private:
	Animation animations[int(AnimationIndex::COUNT)];
	AnimationIndex curAnimation = AnimationIndex::RWALK;
	State state = State::IDLE;
};
