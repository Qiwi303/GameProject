#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Entity.h"
#include "Bullet.h"

class SpaceShip: public Entity{
public:
    inline SpaceShip(sf::Angle angle, const sf::Texture& texture,  float width,  float height,
              float size,const sf::Vector2f& pos,  float maxSpeed, float _acceleration, entityType type);
    inline void takeDmg(float dmg);
    inline virtual void fire(CommonData* cd) = 0;
    inline  void onCollision(Entity* entity);

protected:
    double health = 500;
    bool isFire = false;
    float fireTimer = 0.0f;
};

SpaceShip::SpaceShip(sf::Angle angle, const sf::Texture& texture, const float width, const float height, const float size, const sf::Vector2f& pos,
                     const float maxSpeed, const float _acceleration, const entityType type):
                        Entity(angle, texture, width, height, size, pos, maxSpeed, _acceleration, type) {

    float centerX = rectangle.getGeometricCenter().x;
    float centerY = rectangle.getGeometricCenter().y*1.25f;
    rectangle.setOrigin({centerX, centerY});
}

void SpaceShip::onCollision(Entity* entity) {
    entityType type = entity->getType();
    if (type == playerBullet || type == enemyBullet) {
        takeDmg(dynamic_cast<Bullet*>(entity)->getDmg());
    }
}

void SpaceShip::takeDmg(const float dmg) {
    if (health - dmg>0) health -= dmg;
    else markToDelete = true;
}

#endif //SPACESHIP_H
