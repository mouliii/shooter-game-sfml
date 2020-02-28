#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"



class Player : public Entity
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
public:
	Player(sf::Vector2f pos, BulletManager& bm, TextureManager& tm, std::string path);
	void Update(sf::Vector2f mousepos, std::vector<std::unique_ptr<Entity> >& em, float dt) override;
	virtual void Print() { std::cout << "playerin printti" << std::endl; }
private:
	float speed = 100.f;
	//float width = 16.f;
	//float height = 32.f;
	Animation animations[int(AnimationIndex::COUNT)];
	AnimationIndex curAnimation = AnimationIndex::RWALK;
	
};