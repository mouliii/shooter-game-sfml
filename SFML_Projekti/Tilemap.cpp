#include "Tilemap.h"
#include <fstream>
#include <iostream>

extern const int TILEMAPDIMENSIONS;

Tilemap::Tilemap(TextureManager& tm)
    :
    tm(tm)
{
}

void Tilemap::LoadLevel(std::string filepath, std::string texture_path)
{
    texture = *tm.AcquireTexture(texture_path);

    // lataa mappi ja lue
    std::ifstream in(filepath);
    if (in.good())
    {
        std::cout << "map parsing started" << std::endl;
        sf::Clock _clock;
        float startTime = _clock.getElapsedTime().asMilliseconds();
        std::string str = "";
        std::string tmp;
        while (std::getline(in, tmp)) str += tmp;
        jute::jValue v = jute::parser::parse(str);
        float curTime = _clock.getElapsedTime().asMilliseconds();
        std::cout << "map parsed, time: " << curTime - startTime << " ms" << std::endl;
        // laitetaan mappi tiedot tilemappiin
        dims = v["tilewidth"].as_int();
        mapHeight = v["layers"][0]["height"].as_int();
        mapWidth = v["layers"][0]["width"].as_int();
        nLayers = v["nextlayerid"].as_int() - 1;
        // texture tilet ineen
        for (int i = 0; i < (mapHeight * mapWidth); i++)
        {           
            int n = (v["layers"][0]["data"][i].as_int());   // layer index data
            int rectx = (n % 13 - 1) * TILEMAPDIMENSIONS;   // % is the "modulo operator", the remainder of i / width;
            int recty = (n / 13) * TILEMAPDIMENSIONS;       // where "/" is an integer division

            int posx = i % mapWidth * TILEMAPDIMENSIONS;   // -^sama
            int posy = i / mapWidth * TILEMAPDIMENSIONS;

            std::unique_ptr<Tile> t(new Tile(sf::Vector2f(posx, posy), sf::Vector2f(dims, dims), &texture, sf::IntRect(rectx, recty, dims, dims), sf::Color::Transparent, 1.0f));
            pTiles.push_back(std::move(t));
            /*
            x += dims;
            if (x > mapWidth * TILEMAPDIMENSIONS)
            {
                x = 0;
                y += dims;
            }
            */
        }
        // collision layer
        for (int i = 0; i < mapHeight * mapWidth; i++)
        {
            // teh‰‰ rect
            int posx = i % mapWidth * TILEMAPDIMENSIONS;
            int posy = i / mapWidth * TILEMAPDIMENSIONS;
            sf::IntRect r(posx, posy, dims, dims);
            // jos on joku tile nii collision = true   | jos ei oo mit‰‰ mapis nii 0 default -> nolla ei ole mik‰‰  textuuri
            if (v["layers"][nLayers - 1]["data"][i].as_int() != 0)
            {
                collisionLayer.push_back({ r,true });
            }
            else
            {
                collisionLayer.push_back({ r,false });
            }
        }
        curTime = _clock.getElapsedTime().asMilliseconds();
        std::cout << "level loaded, time: " << curTime - startTime << " ms" << std::endl;
    }
    else
    { 
        std::cout << "loading map failed, senkin Uuno kato filepath" << std::endl;
        std::cout << "kato myˆs et 'nextlayerid' on layerit + 1" << std::endl;
    }
    
}

void Tilemap::AddTile(int layer, sf::Vector2f pos, sf::Vector2f dimensions, sf::Texture texture, sf::IntRect textarea, sf::Color color, float resistance)
{
    std::unique_ptr<Tile> t(new Tile(pos, dimensions, &texture, textarea, color, resistance));
	pTiles.emplace_back(std::move(t));
}

void Tilemap::Draw(sf::RenderTarget& rt, sf::Vector2f topleft, sf::Vector2f botright)
{
    int x = int(topleft.x);
    int y = int(topleft.y);
    int w = int(botright.x);
    int h = int(botright.y);

    for (size_t i = 0; i < (mapHeight * mapWidth); i++)
    {
        rt.draw(pTiles[i]->GetSprite());
    }
    /*
    for (int tempx = x; tempx < w; tempx++)
        {
            for (int tempy = y; tempy < h; tempy++)
            {
                rt.draw(GetTile(i, tempx,tempy)->GetSprite());
            }
        }
    */
}

std::unique_ptr<Tile>& Tilemap::GetTile(int layer, int x, int y)
{

    int index = mapWidth * (y / TILEMAPDIMENSIONS) + (x / TILEMAPDIMENSIONS);
    if (index >= 0 && index < int(pTiles.size()))
    {
        return pTiles[index];
    }
    else
    {
        return pTiles[0];
    }
}

std::pair<sf::IntRect, bool>& Tilemap::GetCollisionRect(int x, int y)
{
    int index = mapWidth * (y / TILEMAPDIMENSIONS) + (x / TILEMAPDIMENSIONS);
    if (index >= 0 && index < int(collisionLayer.size()))
    {
        return collisionLayer[index];
    }
    else
    {
        return collisionLayer[0];
    }
}

/*
switch (c)
            {
            case '.':
            {
                std::unique_ptr<Tile> t(new Tile(sf::Vector2f(x, y), { dims,dims }, tm, sf::IntRect(0,0,1,1), sf::Color::Transparent, true, 1.0f));
                pTiles.emplace_back(std::move(t));
                x += dims;
                break;
            }
            case '0':
            {
                std::unique_ptr<Tile> t(new Tile(sf::Vector2f(x, y), { dims,dims }, tm, sf::IntRect(145,34,16,16), sf::Color(255, 255, 255, 255), false, 0.0f));
                pTiles.emplace_back(std::move(t));
                x += dims;
            }
            break;
            case '1':
            {
                std::unique_ptr<Tile> t(new Tile(sf::Vector2f(x, y), { dims,dims }, tm, sf::IntRect(48, 79, 16, 16), sf::Color(105, 150, 250, 255), false, 0.0f));
                pTiles.emplace_back(std::move(t));
                x += dims;
            }
            break;
            case '3':
            {
                std::unique_ptr<Tile> t(new Tile(sf::Vector2f(x, y), { dims,dims }, tm, sf::IntRect(0, 0, 16, 16), sf::Color(255, 1, 255, 255), false, 0.6f));
                pTiles.emplace_back(std::move(t));
                x += dims;
            }
            break;
            case '\n':
                // rset [x,y]
                while (x / TILEMAPDIMENSIONS < mapWidth)
                {
                    std::unique_ptr<Tile> t(new Tile(sf::Vector2f(x, y), { dims,dims }, tm, sf::IntRect(0, 0, 16, 16), sf::Color::Transparent, true, 1.0f));
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
*/