#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
#include "TextureManager.h"

class Tilemap
{
public:
	Tilemap() = default;
	Tilemap(int tile_dimensions, int mapWidthInTiles, int mapHeightInTiles, TextureManager& tm);
	void LoadLevel(std::string filepath);
	void AddTile(sf::Vector2f pos, sf::Vector2f dimensions, TextureManager& tm, sf::IntRect textarea, sf::Color color, bool passable, float resistance);
	void Draw(sf::RenderTarget& rt);
	std::unique_ptr<Tile>& FindTile(sf::Vector2f tile_cords);
	std::vector<std::unique_ptr<Tile>>& GetTiles() { return pTiles; }
	std::unique_ptr<Tile>& GetTile(int x, int y);
private:
	float dims;
	int mapWidth;
	int mapHeight;
	TextureManager& tm;
	std::vector<std::unique_ptr<Tile>> pTiles;
};