#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Tile
{
public:
	Tile(sf::Vector2f pos, sf::Vector2f dimensions, sf::Texture texture, sf::IntRect Textarea, sf::Color color, float resistance);
	sf::Vector2f GetPixelCoordinate() { return pos; }
	sf::Vector2f GetMapCoordinates();
	sf::Vector2f GetTileDimensions() { return dimensions; }
	void Draw(sf::RenderTarget& rt);
	sf::RectangleShape& GetRect() { return rect; }
	sf::Sprite& GetSprite() { return sprite; }
	const float& GetResistance() { return resistance; }
private:
	sf::RectangleShape rect;
	sf::IntRect area;
	sf::Vector2f pos;
	sf::Vector2f dimensions; // [width , height]
	sf::Sprite sprite;
	sf::Color color;
	float resistance;
	sf::Texture texture;
};
