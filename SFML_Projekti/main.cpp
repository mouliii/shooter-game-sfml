#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "RectCircleCollision.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletManager.h"
/*   vihu dmg -----> tilemap ----> camera ----> 
bullet manager
texture manager
tilemap map

*/
sf::Event event;
sf::Clock _clock;
float curTime = float(_clock.getElapsedTime().asMilliseconds());

BulletManager bm;
Player p(sf::Vector2f(100, 100),&bm);
std::vector<Enemy> enemyArr;


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(1);
    // MAIN LOOP

    float f = 100.f;
    for (int i = 0; i < 5; i++)
    {
        Enemy e(sf::Vector2f(400, f * i + 100));
        enemyArr.push_back(e);
    }
    

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Mouse::Button::Left)
            {
                sf::CircleShape cc = sf::CircleShape(10);
                cc.setPosition(sf::Vector2f(p.GetRect().getPosition()));
                cc.setFillColor(sf::Color::Green);
                cc.setOrigin(sf::Vector2f(cc.getRadius(), cc.getRadius()));
            }
        }
        float dt = _clock.getElapsedTime().asMilliseconds() - curTime;
        dt /= 1000;
        curTime = float(_clock.getElapsedTime().asMilliseconds());
        // INPUT
        sf::Vector2i mPos = sf::Mouse::getPosition(window);

        // UPDATE
        p.Update(sf::Vector2f(mPos),dt);
        for (size_t i = 0; i < bm.GetBullets().size(); i++)
        {
            bm.GetBullets()[i].Update(dt);
        }
        bm.Update(dt);
        for (int i = 0; i < enemyArr.size(); i++)
        {
            enemyArr[i].Update(dt);
        }
        

        //std::cout << mPos.x << std::endl;
        // DRAW
        window.clear();
        p.Draw(window); 
        for (auto d : enemyArr)
        {
            d.Draw(window);
        }
        for (auto b : bm.GetBullets())
        {
            b.Draw(window);
        }
        window.display();
    }

    return 0;
}