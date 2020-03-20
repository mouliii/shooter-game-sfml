#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "BulletManager.h"
#include "EntityManager.h"
#include "Tilemap.h"
#include "Collider.h"
#include "ItemList.h"

//   c/c++ -> code generation -> basic error checking -> Both (/RTC1, equiv. to /RTCsu) (/RTC1) -> default
/*
ongelmat:
    rotate pelaaja hiiren mukaa vai mitenkä
*/
extern const int TILEMAPDIMENSIONS = 16;

sf::Event event;
sf::View view;
sf::Clock _clock;
float curTime = float(_clock.getElapsedTime().asMilliseconds());

Collider collider;
Tilemap tm;
EntityManager em(tm);

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(1);
    view = sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(300.f, 200.f));
    window.setView(view);
    view = getLetterboxView(view, 800, 600);
    tm.LoadLevel("Levels/testimap.json", "textures/tilemap.png",&em);
    std::unique_ptr<Pistol> pistol(new Pistol({ 64.f,105.f}, "textures/Weapons/pistol.png"));
    ItemList::AddWeapon(std::move(pistol));

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
                if (event.mouseButton.button == sf::Mouse::Left)
                {
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
        em.Update(mPos, tm, dt);
        BulletManager::Update(dt);
        collider.Update(&em, tm);
        for (size_t i = 0; i < ItemList::GetWeapons().size(); i++)
        {
            if (em.GetEntities()[0]->GetRect().getGlobalBounds().intersects(ItemList::GetWeapons()[i]->GetRect().getGlobalBounds()))
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                {
                    em.GetEntities()[0]->PickupWeapon(std::move(ItemList::GetWeapons()[i]));
                    ItemList::RemoveWeapon(i);
                }
            }
        }
            // testi
        int x = em.GetEntities()[0]->GetPosCentered().x + 0.5f;
        int y = em.GetEntities()[0]->GetPosCentered().y + 0.5f;
        view.setCenter(em.GetEntities()[0]->GetPosCentered()); // vika update | enne draw
        //std::cout << mPos.y / TILEMAPDIMENSIONS << std::endl;
        
        // DRAW
        window.clear();
        window.setView(view);
        tm.Draw(window, sf::Vector2f(x,y), sf::Vector2f(300.f, 200.f));
        em.Draw(window);
        BulletManager::Draw(window);
        for (size_t i = 0; i < ItemList::GetWeapons().size(); i++)
        {
            ItemList::GetWeapons()[i]->Draw(window);
        }
        window.display();
    }
    return 0;
}


sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float)windowHeight;
    float viewRatio = view.getSize().x / (float)view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));

    return view;
}