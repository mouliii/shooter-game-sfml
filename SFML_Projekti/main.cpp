#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "BulletManager.h"
#include "EntityManager.h"
#include "Tilemap.h"
#include "Collider.h"
#include "ParticleSystem.h"

//   c/c++ -> code generation -> basic error checking -> Both (/RTC1, equiv. to /RTCsu) (/RTC1) -> default
/*
ongelmat:
*/
extern const int TILEMAPDIMENSIONS = 16;

sf::Event event;
sf::View view;
sf::Clock _clock;
float curTime = float(_clock.getElapsedTime().asMilliseconds());

Collider collider;
Tilemap tm;
EntityManager em(tm);

ParticleSystem ps;
ParticleProperties partprop;
bool active = false;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    window.setFramerateLimit(144);
    //window.setVerticalSyncEnabled(1);
    view = sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(1280, 720));
    window.setView(view);
    view.zoom(0.3f); // dungeon_tileset  |    tilemap
    tm.LoadLevel("Levels/level21.json", "textures/dungeon_tileset.png",&em);
    ItemList::AddWeapon(std::make_unique<Pistol>(sf::Vector2f(64.f,105.f), "textures/Weapons/pistol.png"));
    ItemList::AddWeapon(std::make_unique<Ak47>(sf::Vector2f(100.f, 105.f), "textures/Weapons/ak47.png"));

    sf::Music bgm;
    bgm.openFromFile("Sounds/bgm/bgm.flac");
    bgm.setVolume(10.f);
    bgm.play();

    // MAIN LOOP
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
            window.close();
            }
            if (event.type == sf::Event::MouseWheelMoved)
            {
                auto mwd = event.mouseWheelScroll.wheel;
                if (mwd > 0)
                {
                    view.zoom(1.2f);
                }
                else
                {
                    view.zoom(0.8f);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousepos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(mousepos);
                sf::Vector2f mPos = sf::Vector2f(worldPos);
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    active = !active;
                }
            }
        }
        // frame time / dt
        float dt = _clock.getElapsedTime().asMilliseconds() - curTime;
        dt /= 1000;
        curTime = float(_clock.getElapsedTime().asMilliseconds());
        // INPUT
        sf::Vector2i mousepos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousepos);
        sf::Vector2f mPos = sf::Vector2f(worldPos);
        // UPDATE
            //em.Update(mPos, tm, dt);
        BulletManager::Update(dt);
        collider.Update(&em, tm);
        if (active)
        {
            ps.SpawnParticle(mPos, partprop);
        }
        ps.Update(dt);

        // view
        const int maxOffset = 50;
        int x = em.GetEntities()[0]->GetPosCentered().x + 0.5f;
        int y = em.GetEntities()[0]->GetPosCentered().y + 0.5f;
        sf::Vector2f offset = mPos - em.GetEntities()[0]->GetPosCentered();
        offset.x /= 4.f;
        offset.y /= 3.5f;
        const float actualOffset = maxOffset + em.GetEntities()[0]->GetPosCentered().x;
        sf::Vector2f cam = em.GetEntities()[0]->GetPosCentered() + offset;
        cam.x = std::min(std::max(cam.x, view.getSize().x / 2.f), float(tm.GetMapSize().x * TILEMAPDIMENSIONS) - view.getSize().x / 2.f);
        cam.y = std::min(std::max(cam.y, view.getSize().y / 2.f), float(tm.GetMapSize().y * TILEMAPDIMENSIONS) - view.getSize().y / 2.f);
        view.setCenter(cam); // vika update | enne draw
        //std::cout << view.getCenter().x << " " <<  view.getCenter().y << std::endl;
        
        // DRAW
        window.clear();
        window.setView(view);
        tm.Draw(window, view.getCenter() - (view.getSize() / 2.f), view.getSize());
        em.Draw(window);
        BulletManager::Draw(window);
        for (size_t i = 0; i < ItemList::GetWeapons().size(); i++)
        {
            ItemList::GetWeapons()[i]->Draw(window);
        }

        ps.Draw(window);


        window.display();
    }
    return 0;
}