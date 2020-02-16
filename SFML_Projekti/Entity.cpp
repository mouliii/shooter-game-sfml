#include "Entity.h"
#include <iostream>

Entity::Entity(sf::Vector2f pos, BulletManager* bm)
	:
	pos(pos),
	bm(bm)
{
	rect.setSize(sf::Vector2f(50, 50));
	rect.setPosition(pos);
}

void Entity::Update(sf::Vector2f mousepos, float dt)
{
	std::cout << "entity update triggered, voi v**** " << std::endl;
}

void Entity::Draw(sf::RenderTarget& target)
{
	target.draw(rect);
}

sf::RectangleShape Entity::GetRect()
{
	return rect;
}
