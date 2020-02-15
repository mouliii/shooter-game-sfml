#include "Bullet.h"
#include <math.h>


Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir, float radius, float speed, float maxDistance, sf::Color color)
	:
	pos(pos),
	dir(dir),
	radius(radius),
	speed(speed),
	maxDistance(maxDistance),
	color(color)
{
	cc.setOrigin(sf::Vector2f(cc.getRadius(), cc.getRadius()));
	cc.setRadius(radius);
	cc.setPosition(pos);
	cc.setFillColor(color);
	
	delta = dir - pos;
	length = std::sqrt( (delta.x * delta.x) + (delta.y * delta.y) );
	originalPos = pos;
	delta.x /= length;
	delta.y /= length;
}

void Bullet::Update(float dt)
{
	// liikkuminen
	pos.x += speed * delta.x * dt;
	pos.y += speed * delta.y * dt;
	cc.setPosition(pos);
	//collision

	// delete???
	const sf::Vector2f tempPos = pos - originalPos;
	const float dP = std::sqrt((tempPos.x * tempPos.x) + (tempPos.y * tempPos.y));
	//std::cout << maxDistance << std::endl;
	if (dP > maxDistance)
	{
		pop = true;
	}
}

void Bullet::Draw(sf::RenderTarget& rt)
{
	rt.draw(cc);
}


