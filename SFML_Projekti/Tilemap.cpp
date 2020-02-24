#include "Tilemap.h"
#include <fstream>
#include <iostream>

Tilemap::Tilemap(int tile_dimensions)
    :
    dims(float(tile_dimensions) )
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
                std::unique_ptr<Tile> t(new Tile(sf::Vector2f(x, y), { dims,dims }, sf::Color(0, 0, 0, 255), true));
                pTiles.emplace_back(std::move(t));
                x += dims;
                break;
            }
            case '0':
            {
                std::unique_ptr<Tile> t(new Tile(sf::Vector2f(x, y), { dims,dims }, sf::Color(255, 255, 255, 255), false));
                pTiles.emplace_back(std::move(t));
                x += dims;
            }
            break;
            case '1':
            {
                std::unique_ptr<Tile> t(new Tile(sf::Vector2f(x, y), { dims,dims }, sf::Color(105, 150, 250, 255), false));
                pTiles.emplace_back(std::move(t));
                x += dims;
            }
            break;
            case '\n':
                // rset [x,y]
                x = 0;
                y += dims;
                break;
            default:
                // error 'n shit
                break;
            }
        }
    }
}

void Tilemap::AddTile(sf::Vector2f pos, sf::Vector2f dimensions, sf::Color color, bool passable)
{
    std::unique_ptr<Tile> t(new Tile(pos, dimensions, color, passable));
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
