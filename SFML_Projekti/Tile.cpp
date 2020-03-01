#include "Tile.h"

Tile::Tile(sf::Vector2f pos, sf::Vector2f dimensions, TextureManager& tm, sf::IntRect textarea, sf::Color color, bool passable, float resistance)
	:
	pos(pos),
	dimensions(dimensions),
	color(color),
	passable(passable),
	resistance(resistance),
	area(textarea),
	tm(tm)
{
	rect.setSize(sf::Vector2f(dimensions));
	rect.setPosition(sf::Vector2f(pos));
	rect.setFillColor(color);

	sprite.setTexture(*tm.AcquireTexture("textures/lunk.png"));
	sprite.setTextureRect(textarea);
	sprite.setPosition(pos);

}

sf::Vector2f Tile::GetMapCoordinates()
{
	extern const int TILEMAPDIMENSIONS;
	return sf::Vector2f(pos.x / TILEMAPDIMENSIONS, pos.y / TILEMAPDIMENSIONS);
}

void Tile::Draw(sf::RenderTarget & rt)
{
	rt.draw(sprite);
}
