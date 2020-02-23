#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"

class Tilemap
{
public:
	Tilemap(int tile_dimensions);
	void LoadLevel(std::string filepath);
	void AddTile(sf::Vector2f pos, sf::Vector2f dimensions, sf::Color color);
	void Draw(sf::RenderTarget& rt);
private:
	float dims;
	std::vector<Tile> tiles;
};

// DEFAULTTAA ATM 16x16 TILE