#include "Tilemap.h"
#include <fstream>
#include <iostream>
#include "EntityManager.h"

extern const int TILEMAPDIMENSIONS;


void Tilemap::LoadLevel(std::string filepath, std::string texture_path, EntityManager* em)
{   // 0 - texture | 1 - texture | 2 - collision | 3 - object
    texture = *TextureManager::AcquireTexture(texture_path);
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
        nObjects = v["nextobjectid"].as_int() - 1; 
        // tilemap texture size
        textureWidth = texture.getSize().x / dims;
        textureHeight = texture.getSize().y / dims;
        std::cout << "map dimensions: " << "[" << mapWidth << "," << mapHeight << "]" << '\n' << "texture dims: " << "[" << textureWidth << "," << textureHeight << "]" << '\n' << "Layers: " << nLayers << std::endl;
        std::cout << "nObjects: " << nObjects << std::endl;
        ////// TESTI TODO
        for (size_t i = 0; i < nLayers; i++)
        {
            std::string n = "";
            try
            {
                n = (v["layers"][i]["name"].as_string());
                if (n == "")
                {
                    throw std::exception("mapin lataamisessa virhe, ei ole esim. pelaaja ");
                }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
                break;
            }
            if (n.find("Tile") != std::string::npos)
            {
                std::vector<std::unique_ptr<Tile>> l;
                for (int t = 0; t < (mapHeight * mapWidth); t++)
                {
                    int n = (v["layers"][i]["data"][t].as_int());   // layer index data
                    int rectx = (n % textureWidth - 1) * TILEMAPDIMENSIONS;   // % is the "modulo operator", the remainder of i / width;
                    int recty = (n / textureWidth) * TILEMAPDIMENSIONS;       // where "/" is an integer division

                    int posx = t % mapWidth * TILEMAPDIMENSIONS;   // -^sama
                    int posy = t / mapWidth * TILEMAPDIMENSIONS;
                    l.emplace_back(std::make_unique<Tile>(sf::Vector2f(float(posx), float(posy)), sf::Vector2f(float(dims), float(dims)), &texture, sf::IntRect(rectx, recty, dims, dims), sf::Color::Transparent, 1.0f));
                }
                pTiles.emplace_back(std::move(l));
            }
            else if (n.find("collision") != std::string::npos)
            {
                for (int c = 0; c < mapHeight * mapWidth; c++)
                {
                    // teh‰‰ rect
                    int posx = c % mapWidth * TILEMAPDIMENSIONS;
                    int posy = c / mapWidth * TILEMAPDIMENSIONS;
                    sf::IntRect r(posx, posy, int(dims), int(dims));
                    // jos on joku tile nii collision = true   | jos ei oo mit‰‰ mapis nii 0 default -> nolla ei ole mik‰‰  textuuri
                    if (v["layers"][i]["data"][c].as_int() != 0)
                    {
                        collisionLayer.push_back({ r,true });
                    }
                    else
                    {
                        collisionLayer.push_back({ r,false });
                    }
                }
            }
            else if (n.find("Object") != std::string::npos)
            {
                for (int o = 0; o < nObjects; o++)
                {
                    try
                    {
                        v["layers"][i]["objects"][o]["id"].as_int();
                    }
                    catch (const std::exception&)
                    {
                        break;
                    }
                    std::string obj = v["layers"][i]["objects"][o]["name"].as_string();
                    int x = v["layers"][i]["objects"][o]["x"].as_int();
                    int y = v["layers"][i]["objects"][o]["y"].as_int();
                    if (obj == "player_spawn")
                    {
                        em->AddEntity(std::make_unique<Player>(sf::Vector2f(x, y), *this, "textures/lunk.png"));
                        std::vector<int> asd;
                        int id = v["layers"][i]["objects"][o]["id"].as_int();
                        if (id != 1)
                        {
                            std::swap(em->GetEntities()[0], em->GetEntities()[em->GetEntities().size() - 1]);
                        }
                    }
                    else if (obj == "enemy_spawn")
                    {
                        em->AddEntity(std::make_unique<Enemy>(sf::Vector2f(x, y), *this, "textures/lunk.png"));
                    }
                    else if (obj == "level_trigger")
                    {

                    }
                }
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
    int x = int(topleft.x)  / TILEMAPDIMENSIONS;
    int y = int(topleft.y)  / TILEMAPDIMENSIONS;
    int w = int(botright.x) / TILEMAPDIMENSIONS;
    int h = int(botright.y) / TILEMAPDIMENSIONS;
    
    for (size_t i = 0; i < pTiles.size(); i++)
    {
        for (int j = 0; j < (mapHeight * mapWidth); j++)
        {
            rt.draw(pTiles[i][j]->GetSprite());
        }
    }
    /*
    // TODO
    //std::cout << w << std::endl;
    for (size_t i = 0; i < pTiles.size(); i++)
    {
        for (int tempx = x; tempx < w; tempx++)
        {
            for (int tempy = y; tempy < h; tempy++)
            {
                // index 0 sadkosakdoask <...-
                rt.draw(GetTile(i, tempx, tempy)->GetSprite());
            }
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