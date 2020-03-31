#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "RectCircleCollision.h"
#include "AStar.h"

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
		AGGROED,
		MOVING
	};
public:
	Enemy(sf::Vector2f pos, Tilemap& tilemap, std::string path);
	virtual void Update(sf::Vector2f mpos, std::vector<std::unique_ptr<Entity>>& em, Tilemap& tm, float dt) override;
	const int GetHp() { return hp; }
	void Print() override { std::cout << "vihu" << std::endl;}
	void UpdateAstar(sf::Vector2i startPosCentered, sf::Vector2i endPosCentered);
	void UpdateMovement(std::vector<std::unique_ptr<Entity> >& em, float dt);
private:
	float speed = 70.f;
	// a star path finding
	Astar aStar;
	std::vector<sf::Vector2i> pathVec;
	int pathIndex = 0;
	sf::Vector2i aStarTarget = { 0,0 };
	sf::Vector2i originalPos = sf::Vector2i(int(pos.x), int(pos.y));
	float idleTimer = float(Random::GetRandomInt(0, 100) / 10.f);
private:
	Animation animations[int(AnimationIndex::COUNT)];
	AnimationIndex curAnimation = AnimationIndex::RWALK;
	State state = State::IDLE;
};
