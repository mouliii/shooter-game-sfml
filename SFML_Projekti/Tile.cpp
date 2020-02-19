#include "Tile.h"

Tile::Tile(sf::Vector2f pos, sf::Vector2f dimensions, sf::Color color)
	:
	pos(pos),
	dimensions(dimensions),
	color(color)
{
	rect.setSize(sf::Vector2f(dimensions));
	rect.setPosition(sf::Vector2f(pos));
	rect.setFillColor(color);
}

void Tile::Draw(sf::RenderTarget & rt)
{
	rt.draw(rect);
}
