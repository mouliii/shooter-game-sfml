#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "RectCircleCollision.h"
#include "BulletManager.h"
#include "EntityManager.h"
/*   vihu dmg -----> tilemap ----> camera ----> 
managerit k‰ytt‰m‰‰n smart poibntereita asd 
tilemap map

*/
sf::Event event;
sf::Clock _clock;
float curTime = float(_clock.getElapsedTime().asMilliseconds());
EntityManager em;
BulletManager bm;
Player p({ 100.f,100.f }, &bm);


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(1);
    // MAIN LOOP
    em.AddEntity(p);
    Enemy e({ 150.f, 200.f }, &bm);
    em.AddEntity(e);
    //////////
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
            window.close();
            }
        }
        // frame time / dt
        float dt = _clock.getElapsedTime().asMilliseconds() - curTime;
        dt /= 1000;
        curTime = float(_clock.getElapsedTime().asMilliseconds());
        // INPUT
        sf::Vector2i mousepos = sf::Mouse::getPosition(window);
        sf::Vector2f mPos = sf::Vector2f(mousepos);
        // UPDATE
        em.Update(mPos, dt);
        bm.Update(dt);

        //std::cout << mPos.x << std::endl;
        // DRAW
        window.clear();
        em.Draw(window);
        bm.Draw(window);
        window.display();
    }

    return 0;
}