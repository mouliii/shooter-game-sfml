#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
public:
	Tile(sf::Vector2f pos, sf::Vector2f dimensions,sf::Color color, bool passable);
	sf::Vector2f GetPixelCoordinate() { return pos; }
	sf::Vector2f GetMapCoordinates();
	sf::Vector2f GetTileDimensions() { return dimensions; }
	void Draw(sf::RenderTarget& rt);
	sf::RectangleShape& GetRect() { return rect; }
	bool isPassable() { return passable; }
private:
	sf::RectangleShape rect;
	sf::Vector2f pos;
	sf::Vector2f dimensions; // [width , height]
	sf::Color color;
	bool passable;
};
