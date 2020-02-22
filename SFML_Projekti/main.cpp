#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "BulletManager.h"
#include "EntityManager.h"
#include "Tilemap.h"
#include "Collider.h"
/*   swept AABB -----> texturet ------> draw manager , layer based -------->
managerit k�ytt�m��n smart poibntereita asd 
tilemap map
TILEMAP DEFAULTTAA 16x16 ATM !!!!  <----------
kamera - pelaaja kulmat
fixed const int/float size tile 'n shit
*/
/*
ongelmat
random vector out of range, ei tullu uudestaa
16x16 onks hyv�?
*/
sf::Event event;
sf::Clock _clock;
float curTime = float(_clock.getElapsedTime().asMilliseconds());
sf::View view;
EntityManager em;
BulletManager bm;
Tilemap tm;
Collider collider;
Player p({ -20.f, -20.f }, &bm);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(1);
    view = sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(300.f, 200.f));
    window.setView(view);
    // MAIN LOOP
    tm.LoadLevel("level.txt");
    em.AddEntity(p);

    //Enemy e({ 150.f, 200.f }, &bm);
    //em.AddEntity(e);
    //////////
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
        em.Update(mPos, em.GetEntities(), dt);
        bm.Update(&em,dt);
        collider.Update(em.GetEntities(), tm.GetTiles() );

        view.setCenter(p.GetPosCentered()); // vika update | enne draw
        //std::cout << event.mouseWheel.delta << std::endl;
        // DRAW
        window.clear();
        window.setView(view);
        tm.Draw(window);
        em.Draw(window);
        bm.Draw(window);
        window.display();
    }

    return 0;
}