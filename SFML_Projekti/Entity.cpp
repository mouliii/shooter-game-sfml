#include "Entity.h"

Entity::Entity(sf::Vector2f pos, BulletManager& bm, TextureManager& tm, Tilemap& tilemap, std::string path)
	:
	pos(pos),
	bm(bm),
	tm(tm),
	tilemap(tilemap)
{
	rect.setSize(sf::Vector2f(width,height));
	rect.setPosition(pos);

	sprite.setTexture(*tm.AcquireTexture(path));
	sprite.setPosition(pos);

}

Entity::~Entity()
{
}

void Entity::Update(sf::Vector2f mousepos, std::vector<std::unique_ptr<Entity> >& em, Tilemap& tm, float dt)
{
	std::cout << "entity update triggered, voi v**** " << std::endl;
}

void Entity::Draw(sf::RenderTarget& target)
{
	target.draw(sprite);
	sf::RectangleShape temp;
	temp.setPosition(rect.getPosition());
	temp.setSize(rect.getSize());
	temp.setOutlineThickness(0.5f);
	temp.setOutlineColor(sf::Color(255, 255, 255));
	temp.setFillColor(sf::Color::Transparent);
	target.draw(temp);
}

sf::RectangleShape& Entity::GetRect()
{
	return rect;
}

sf::Vector2f Entity::GetPosCentered()
{
	return sf::Vector2f(GetPos().x + GetRect().getLocalBounds().width / 2, GetPos().y + GetRect().getLocalBounds().height / 2);
}
