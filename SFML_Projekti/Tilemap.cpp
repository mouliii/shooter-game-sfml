#include "Tilemap.h"
#include <fstream>
#include <iostream>

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
                // tile 1
                x += 16;
                break;
            case '0':
            {
                Tile t(sf::Vector2f(x, y), { 16,16 }, sf::Color(255, 255, 255, 255));
                tiles.push_back(t);
                x += 16;
            }
            break;
            case '1':
            {
                Tile t(sf::Vector2f(x, y), { 16,16 }, sf::Color(105, 150, 200, 255));
                tiles.push_back(t);
                x += 16;
            }
            break;
            case '\n':
                // rset [x,y]
                x = 0;
                y += 16;
                break;
            default:
                // error 'n shit
                break;
            }
        }
    }
}

void Tilemap::AddTile(sf::Vector2f pos, sf::Vector2f dimensions, sf::Color color)
{
	Tile t(pos, dimensions, color);
	tiles.push_back(t);
}

void Tilemap::Draw(sf::RenderTarget& rt)
{
	for (auto& t : tiles)
	{
		rt.draw(t.GetRect());
	}
}
