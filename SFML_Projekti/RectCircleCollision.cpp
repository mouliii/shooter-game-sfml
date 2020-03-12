#pragma once
#include <math.h>
#include "RectCircleCollision.h"

CRCollision& CRCollision::Get()
{
	static CRCollision instance;
	return instance;
}

bool CRCollision::CircleRectCollision(sf::CircleShape c, sf::RectangleShape r)
{
	return Get().I_CircleRectCollision(c, r);
}

bool CRCollision::CircleRectCollision(sf::CircleShape c, sf::IntRect r)
{
    return Get().I_CircleRectCollision(c,r);
}

bool CRCollision::I_CircleRectCollision(sf::CircleShape c, sf::RectangleShape r)
{
    float cx = c.getPosition().x;
    float cy = c.getPosition().y;
    float radius = c.getRadius();

    float rx = r.getPosition().x;
    float ry = r.getPosition().y;
    float rw = r.getSize().x;
    float rh = r.getSize().y;
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

bool CRCollision::I_CircleRectCollision(sf::CircleShape c, sf::IntRect r) {

    float cx = c.getPosition().x;
    float cy = c.getPosition().y;
    float radius = c.getRadius();

    float rx = r.left;
    float ry = r.top;
    float rw = r.width;
    float rh = r.height;
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
