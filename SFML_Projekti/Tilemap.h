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
	void LoadLevel(std::string filepath, std::string texture_path, class EntityManager* em);
	void Draw(sf::RenderTarget& rt, sf::Vector2f topleft, sf::Vector2f botright);
	std::unique_ptr<Tile>& GetTile(int layer, int x, int y);
	std::pair<sf::IntRect, bool>& GetCollisionRect(int x, int y);
	size_t GetCollisionLayerSize() { return collisionLayer.size(); }
	std::vector<std::pair<sf::IntRect, bool>>& GetCollisionLayer() { return collisionLayer; }
	const sf::Vector2i GetMapSize() { return sf::Vector2i(mapWidth, mapHeight); }
	const int tileSize() { return dims; }
private:
	int nLayers = 0;
	int nObjects = 0;
	int dims = 0;
	int mapWidth = 0;
	int mapHeight = 0;
	int textureWidth = 0;
	int textureHeight = 0;
	sf::Texture texture;
	std::vector<std::vector<std::unique_ptr<Tile>>> pTiles;
	std::vector<std::pair<sf::IntRect, bool>> collisionLayer;
};