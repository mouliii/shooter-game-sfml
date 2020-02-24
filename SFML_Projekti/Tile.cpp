#include "Tile.h"

Tile::Tile(sf::Vector2f pos, sf::Vector2f dimensions, sf::Color color, bool passable)
	:
	pos(pos),
	dimensions(dimensions),
	color(color),
	passable(passable)
{
	rect.setSize(sf::Vector2f(dimensions));
	rect.setPosition(sf::Vector2f(pos));
	rect.setFillColor(color);
}

sf::Vector2f Tile::GetMapCoordinates()
{
	extern const int TILEMAPDIMENSIONS;
	return sf::Vector2f(pos.x / TILEMAPDIMENSIONS, pos.y / TILEMAPDIMENSIONS);
}

void Tile::Draw(sf::RenderTarget & rt)
{
	rt.draw(rect);
}
