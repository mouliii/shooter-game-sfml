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
        float startTime = float(_clock.getElapsedTime().asMilliseconds());
        std::string str = "";
        std::string tmp;
        while (std::getline(in, tmp)) str += tmp;
        jute::jValue v = jute::parser::parse(str);
        float curTime = float(_clock.getElapsedTime().asMilliseconds());
        std::cout << "map parsed, time: " << curTime - startTime << " ms" << std::endl;
        // laitetaan mappi tiedot tilemappiin
        dims = v["tilewidth"].as_int();
        mapHeight = v["layers"][0]["height"].as_int();
        mapWidth = v["layers"][0]["width"].as_int();
        nLayers = v["nextlayerid"].as_int() - 1;
        // tilemap texture size
        textureWidth = texture.getSize().x / dims;
        textureHeight = texture.getSize().y / dims;
        std::cout << "map dimensions: " << "[" << mapWidth << "," << mapHeight << "]" << '\n' << "texture dims: " << "[" << textureWidth << "," << textureHeight << "]" << '\n' << "Layers: " << nLayers << std::endl;
        // texture tilet ineen
        std::vector<std::unique_ptr<Tile>> l;
        for (int j = 0; j <= nLayers - 2; j++)
        {
            for (int i = 0; i < (mapHeight * mapWidth); i++)
            {
                int n = (v["layers"][j]["data"][i].as_int());   // layer index data
                int rectx = (n % textureWidth - 1) * TILEMAPDIMENSIONS;   // % is the "modulo operator", the remainder of i / width;
                int recty = (n / textureWidth) * TILEMAPDIMENSIONS;       // where "/" is an integer division

                int posx = i % mapWidth * TILEMAPDIMENSIONS;   // -^sama
                int posy = i / mapWidth * TILEMAPDIMENSIONS;

                std::unique_ptr<Tile> t(new Tile(sf::Vector2f(float(posx), float(posy)), sf::Vector2f(float(dims), float(dims)), &texture, sf::IntRect(rectx, recty, dims, dims), sf::Color::Transparent, 1.0f));
                l.emplace_back(std::move(t));
            }
            pTiles.emplace_back(std::move(l));
            l.clear();
        }
       
        // collision layer
        for (int i = 0; i < mapHeight * mapWidth; i++)
        {
            // teh‰‰ rect
            int posx = i % mapWidth * TILEMAPDIMENSIONS;
            int posy = i / mapWidth * TILEMAPDIMENSIONS;
            sf::IntRect r(posx, posy, int(dims), int(dims));
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
        curTime = float(_clock.getElapsedTime().asMilliseconds());
        std::cout << "level loaded, time: " << curTime - startTime << " ms" << std::endl;
    }
    else
    { 
        std::cout << "loading map failed, senkin Uuno kato filepath" << std::endl;
        std::cout << "kato myˆs et 'nextlayerid' on layerit + 1" << std::endl;
    }
}

void Tilemap::Draw(sf::RenderTarget& rt, sf::Vector2f topleft, sf::Vector2f botright)
{
    int x = int(topleft.x);
    int y = int(topleft.y);
    int w = int(botright.x);
    int h = int(botright.y);
    for (int i = 0; i < pTiles.size(); i++)
    {
        for (int j = 0; j < (mapHeight * mapWidth); j++)
        {
            rt.draw(pTiles[i][j]->GetSprite());
        }
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
    if (index >= 0 && index < int(pTiles[layer].size()))
    {
        return pTiles[layer][index];
    }
    else
    {
        return pTiles[0][0];
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