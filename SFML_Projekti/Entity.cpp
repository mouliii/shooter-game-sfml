#include "Entity.h"

extern const int TILEMAPDIMENSIONS;

Entity::Entity(sf::Vector2f pos, Tilemap& tilemap, std::string texture_path)
	:
	pos(pos),
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
	if (weapon != nullptr)
	{
		weapon->Draw(target);
	}
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

bool Entity::LineofSight(sf::Vector2f origin, sf::Vector2f dest, int maxRange, int precision)
{
	// normalize delta vectori
	sf::Vector2f delta = dest - origin;
	float distance = std::sqrt((delta.x * delta.x) + (delta.y * delta.y));
	delta.x /= distance;
	delta.y /= distance;

	//int precision = precision; // How many steps to check, must be smaller than pixel width/height of a tile

	if (distance > maxRange) { // If target is out of range, do not check LOS
		return false;
	}
	else
	{
		int iterations = (int)distance / precision;
		for (int x = 1; x < iterations; x++)
		{
			// TileMap.IsWallTileByPixel(origin + stepDirection * (x * 25))
			int stepX = origin.x + delta.x * (x * TILEMAPDIMENSIONS / 2);
			int stepY = origin.y + delta.y * (x * TILEMAPDIMENSIONS / 2);
			if (tilemap.GetCollisionRect(stepX,stepY).second)
			{
				return false;
			}
		}
		return true; // If no wall tiles were found LOS is clear
	}
}

void Entity::PickupWeapon(std::unique_ptr<Weapon>& wep)
{
	if (weapon == nullptr)
	{
		weapon = std::move(wep);
	}
	else
	{
		std::unique_ptr<Weapon> temp;
		temp = std::move(weapon);
		weapon = std::move(wep);
		wep = std::move(temp);
	}
}
