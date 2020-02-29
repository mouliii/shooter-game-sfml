#include "Tilemap.h"
#include <fstream>
#include <iostream>

extern const int TILEMAPDIMENSIONS;

Tilemap::Tilemap(int tile_dimensions, int mapWidthInTiles, int mapHeightInTiles)
    :
    dims(float(tile_dimensions) ),
    mapWidth(mapWidthInTiles),
    mapHeight(mapHeightInTiles)
{
}

void Tilemap::LoadLevel(std::string filepath)
{
    float x = 0;
    float y = 0;
    std::ifstream in(filepath);
    if (!in)
    {
        std::cout << "Failed to load file. Check filepath" << std::endl;
    }
    else
    {
        for (char c = in.get(); in.good(); c = in.get())
        {
            switch (c)
            {
            case '.':
            {
                std::unique_ptr<Tile> t(new Tile(sf::Vector2f(x, y), { dims,dims }, sf::Color::Transparent, true, 1.0f));
                pTiles.emplace_back(std::move(t));
                x += dims;
                break;
            }
            case '0':
            {
                std::unique_ptr<Tile> t(new Tile(sf::Vector2f(x, y), { dims,dims }, sf::Color(255, 255, 255, 255), false, 0.0f));
                pTiles.emplace_back(std::move(t));
                x += dims;
            }
            break;
            case '1':
            {
                std::unique_ptr<Tile> t(new Tile(sf::Vector2f(x, y), { dims,dims }, sf::Color(105, 150, 250, 255), false, 0.0f));
                pTiles.emplace_back(std::move(t));
                x += dims;
            }
            break;
            case '3':
            {
                std::unique_ptr<Tile> t(new Tile(sf::Vector2f(x, y), { dims,dims }, sf::Color(255, 1, 255, 255), false, 0.6f));
                pTiles.emplace_back(std::move(t));
                x += dims;
            }
            break;
            case '\n':
                // rset [x,y]
                while (x / TILEMAPDIMENSIONS < mapWidth)
                {
                    std::unique_ptr<Tile> t(new Tile(sf::Vector2f(x, y), { dims,dims }, sf::Color::Transparent, true, 1.0f));
                    pTiles.emplace_back(std::move(t));
                    x += dims;
                }
                x = 0;
                y += dims;
                break;
            default:
                // error 'n shit
                break;
            }
        }
        while (y / TILEMAPDIMENSIONS < mapHeight)
        {
            while (x / TILEMAPDIMENSIONS < mapWidth)
            {
                std::unique_ptr<Tile> t(new Tile(sf::Vector2f(x, y), { dims,dims }, sf::Color::Transparent, true, 1.0f));
                pTiles.emplace_back(std::move(t));
                x += dims;
            }
            x = 0;
            y += dims;
        }
    }
}

void Tilemap::AddTile(sf::Vector2f pos, sf::Vector2f dimensions, sf::Color color, bool passable, float resistance)
{
    std::unique_ptr<Tile> t(new Tile(pos, dimensions, color, passable, resistance));
	pTiles.emplace_back(std::move(t));
}

void Tilemap::Draw(sf::RenderTarget& rt)
{
	for (auto& t : pTiles)
	{
		rt.draw(t->GetRect());
	}
}

std::unique_ptr<Tile>& Tilemap::FindTile(sf::Vector2f tile_cords)
{
    for (auto& t : pTiles)
    {
        if (t->GetMapCoordinates() == tile_cords)
        {
            return t;
        }
    }
    std::cout << "EI LOYDY TIILIA" << std::endl;
    return pTiles[0];
}

std::unique_ptr<Tile>& Tilemap::GetTile(int x, int y)
{
    if (y < 0)
    {
        y = 0;
    }
    else if ( y > mapHeight - 1)
    {
        y = mapHeight - 1;
    }
    if (x < 0)
    {
        x = 0;
    }
    else if (x > mapWidth - 1 )
    {
        x = mapWidth - 1;
    }

    int index = mapWidth * y + x;
    if (index >= 0 && index < pTiles.size())
    {
        return pTiles[index];
    }
    else
    {
        return pTiles[0];
    }
}
