#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "BulletManager.h"
#include "EntityManager.h"
#include "Tilemap.h"
#include "Collider.h"
//   idle animaatio ---> rework tile map

/*
ongelmat
check vaa ympärillä olevat tilet
16x16 onks hyvä?
liikkuvat tilet kusee !!
*/
extern const int TILEMAPDIMENSIONS = 16;

sf::Event event;
sf::View view;
sf::Clock _clock;
float curTime = float(_clock.getElapsedTime().asMilliseconds());

EntityManager em;
Collider collider;
TextureManager textures;
Tilemap tm(TILEMAPDIMENSIONS, 12, 10, textures);
BulletManager bm(tm);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(1);
    view = sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(300.f, 200.f));
    window.setView(view);
    // MAIN LOOP
    tm.LoadLevel("level2.txt");
    std::unique_ptr<Player> p(new Player({ 60.f,35.f }, bm, textures,"textures/lunk.png"));
    std::unique_ptr<Enemy> e(new Enemy({ 30.f,18.f }, bm, textures, "textures/lunk.png"));
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
        collider.Update(em.GetEntities(), tm);
        view.setCenter(em.GetEntities()[0]->GetPosCentered()); // vika update | enne draw
        //std::cout << mPos.y / TILEMAPDIMENSIONS << std::endl;
        sf::RectangleShape rs;
        rs.setPosition(tm.GetTile( int(mPos.x / TILEMAPDIMENSIONS), int(mPos.y / TILEMAPDIMENSIONS))->GetRect().getPosition());
        rs.setSize(tm.GetTile( int(mPos.x / TILEMAPDIMENSIONS), int(mPos.y / TILEMAPDIMENSIONS))->GetRect().getSize());
        rs.setOutlineThickness(0.5f);
        rs.setOutlineColor(sf::Color(255, 0, 0));
        rs.setFillColor(sf::Color::Transparent);
        // DRAW
        window.clear();
        window.setView(view);
        tm.Draw(window);
        em.Draw(window);
        bm.Draw(window);
        window.draw(rs);
        window.display();
    }

    return 0;
}