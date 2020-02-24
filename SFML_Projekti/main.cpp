#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "BulletManager.h"
#include "EntityManager.h"
#include "Tilemap.h"
#include "Collider.h"
//   bullet collision ---->  entity - tile collision | ei kaikkia tilejä vaa array ---->

/*
ongelmat
random vector out of range, ei tullu uudestaa
16x16 onks hyvä?
*/
extern const int TILEMAPDIMENSIONS = 16;

sf::Event event;
sf::View view;
sf::Clock _clock;
float curTime = float(_clock.getElapsedTime().asMilliseconds());

EntityManager em;
Tilemap tm(TILEMAPDIMENSIONS);
BulletManager bm(tm);
Collider collider;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(1);
    view = sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(300.f, 200.f));
    window.setView(view);
    // MAIN LOOP
    tm.LoadLevel("level.txt");
    std::unique_ptr<Player> p(new Player({ 20.f,20.f }, &bm));
    std::unique_ptr<Enemy> e(new Enemy({ 18.f,18.f }, &bm));
    em.AddEntity(std::move(p) );
    em.AddEntity(std::move(e));

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
        em.Update(mPos, dt);
        bm.Update(&em,dt);
        collider.Update(em.GetEntities(), tm.GetTiles());
        view.setCenter(em.GetEntities()[0]->GetPosCentered()); // vika update | enne draw
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