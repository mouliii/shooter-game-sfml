#include "Entity.h"

extern const int TILEMAPDIMENSIONS;

Entity::Entity(sf::Vector2f pos, BulletManager& bm, Tilemap& tilemap, std::string texture_path)
	:
	pos(pos),
	bm(bm),
	tilemap(tilemap),
	aStar(tilemap)
{
	rect.setSize(sf::Vector2f(width,height));
	rect.setPosition(pos);
	sprite.setTexture(*TextureManager::AcquireTexture(texture_path));
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

void Entity::UpdateAstar(sf::Vector2i startPosCentered, sf::Vector2i endPosCentered)
{
	aStar.Solve_AStar(startPosCentered, endPosCentered, tilemap.GetCollisionLayer());
	pathVec.clear();
	pathVec = aStar.GetPathVector();
	std::reverse(pathVec.begin(), pathVec.end());
	if (!pathVec.empty())
	{
		aStarTarget.x = pathVec[pathIndex].x * TILEMAPDIMENSIONS;
		aStarTarget.y = pathVec[pathIndex].y * TILEMAPDIMENSIONS;
	}
}

const sf::Vector2i Entity::GetPosInTilesCentered()
{
	return sf::Vector2i((int(pos.x) + int(width) / 2) / TILEMAPDIMENSIONS, (int(pos.y) + int(height) / 2) / TILEMAPDIMENSIONS);
}
