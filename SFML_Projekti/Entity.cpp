#include "Entity.h"

Entity::Entity(sf::Vector2f pos, BulletManager* bm)
	:
	pos(pos),
	bm(bm)
{
	rect.setSize(sf::Vector2f(dims,dims));
	rect.setPosition(pos);
}

Entity::~Entity()
{
}

void Entity::Update(sf::Vector2f mousepos, std::vector<std::unique_ptr<Entity> >& em, float dt)
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

sf::Vector2f Entity::GetPosCentered()
{
	return sf::Vector2f(GetPos().x + GetRect().getLocalBounds().width / 2, GetPos().y + GetRect().getLocalBounds().height / 2);
}
