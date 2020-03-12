#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>


class CRCollision
{
public:
    CRCollision(const CRCollision&) = delete;
    static CRCollision& Get();
    static bool CircleRectCollision(sf::CircleShape c, sf::RectangleShape r);
    static bool CircleRectCollision(sf::CircleShape c, sf::IntRect r);
private:
    CRCollision() {}
    bool I_CircleRectCollision(sf::CircleShape c, sf::RectangleShape r);
    bool I_CircleRectCollision(sf::CircleShape c, sf::IntRect r);
};