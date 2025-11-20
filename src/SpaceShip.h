#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Entity.h"
#include "Bullet.h"

class SpaceShip: public Entity{
public:
    SpaceShip(sf::Angle _angle, const std::filesystem::path& texture, const float width, const float height, const float size, float _x, float _y): Entity(_angle, texture, width, height, size, _x, _y) {
        x = (widthOfWindow - width)/2;
        y = (heightWindow - height)/2;

        rectangle.setPosition({(widthOfWindow - width)/2, (heightWindow - height)/2});
        float centerX = rectangle.getGeometricCenter().x;
        float centerY = rectangle.getGeometricCenter().y*1.25f;
        rectangle.setOrigin({centerX, centerY});
    }
    virtual void fire(CommonData* cd) = 0;

protected:
    //double health;

};

#endif //SPACESHIP_H
