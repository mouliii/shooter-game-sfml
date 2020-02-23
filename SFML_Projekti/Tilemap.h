#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"

class Tilemap
{
public:
	Tilemap(int tile_dimensions);
	void LoadLevel(std::string filepath);
	void AddTile(sf::Vector2f pos, sf::Vector2f dimensions, sf::Color color, bool passable);
	void Draw(sf::RenderTarget& rt);
	std::vector<std::unique_ptr<Tile>>& GetTiles() { return pTiles; }
private:
	float dims;
	std::vector<std::unique_ptr<Tile>> pTiles;
};