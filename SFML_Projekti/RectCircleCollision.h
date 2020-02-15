#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

// CIRCLE/RECTANGLE
bool CircleRectCollision(sf::CircleShape c, sf::RectangleShape r) {

    float cx = c.getPosition().x;
    float cy = c.getPosition().y;
    float radius = c.getRadius();

    float rx = r.getPosition().x;
    float ry = r.getPosition().y;
    float rw = r.getGlobalBounds().width;
    float rh = r.getGlobalBounds().height;
    // temporary variables to set edges for testing
    float testX = c.getPosition().x;
    float testY = c.getPosition().y;

    // which edge is closest?
    if (cx < rx) {
        testX = rx;         // test left edge
    }
    else if (cx > rx + rw) {
        testX = rx + rw;   // right edge
    }
    if (cy < ry) {
        testY = ry;        // top edge
    }
    else if (cy > ry + rh) {
        testY = ry + rh;   // bottom edge
    }

    // get distance from closest edges
    float distX = cx - testX;
    float distY = cy - testY;
    float distance = sqrt((distX * distX) + (distY * distY));

    // if the distance is less than the radius, collision!
    if (distance <= radius) {
        return true;
    }
    return false;
}