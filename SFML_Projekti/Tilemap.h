#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"

class Tilemap
{
public:
	Tilemap() = default;
	void LoadLevel(std::string filepath);
	void AddTile(sf::Vector2f pos, sf::Vector2f dimensions, sf::Color color, bool passable);
	void Draw(sf::RenderTarget& rt);
	std::vector<Tile*> GetTiles();
private:
	std::vector<Tile> tiles;
};

// DEFAULTTAA ATM 16x16 TILE