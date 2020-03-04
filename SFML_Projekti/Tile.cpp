#include "Tile.h"

Tile::Tile(sf::Vector2f pos, sf::Vector2f dimensions, sf::Texture texture, sf::IntRect textarea, sf::Color color, float resistance)
	:
	pos(pos),
	dimensions(dimensions),
	color(color),
	resistance(resistance),
	area(textarea)
{
	rect.setSize(sf::Vector2f(dimensions));
	rect.setPosition(sf::Vector2f(pos));
	rect.setFillColor(color);

	sprite.setTexture(texture);
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
