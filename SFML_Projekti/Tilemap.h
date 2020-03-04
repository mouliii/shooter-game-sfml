#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
#include "TextureManager.h"
#include "jute.h"



class Tilemap
{
public:
	Tilemap() = default;
	Tilemap(TextureManager& tm);
	void LoadLevel(std::string filepath, std::string texture_path);
	void AddTile(sf::Vector2f pos, sf::Vector2f dimensions, sf::Texture texture, sf::IntRect textarea, sf::Color color, float resistance);
	void Draw(sf::RenderTarget& rt, sf::Vector2f topleft, sf::Vector2f botright);
	std::unique_ptr<Tile>& GetTile(int layer, int x, int y);
private:
	int nLayers = 0;
	float dims = 0.0f;
	int mapWidth = 0;
	int mapHeight = 0;
	TextureManager& tm;
	sf::Texture texture;
	std::vector<std::vector<std::unique_ptr<Tile>>> pTiles;
	std::vector<std::pair<sf::IntRect, bool>> collisionLayer;
};