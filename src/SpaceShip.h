#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Entity.h"
#include "Bullet.h"

class SpaceShip: public Entity{
public:
    SpaceShip(sf::Angle _angle, const std::filesystem::path& texture, const float width, const float height, const float size, const sf::Vector2f& _pos, entityType type ): Entity(_angle, texture, width, height, size, _pos, type) {
        float centerX = rectangle.getGeometricCenter().x;
        float centerY = rectangle.getGeometricCenter().y*1.25f;
        rectangle.setOrigin({centerX, centerY});
    }

    void takeDmg(float dmg);
    inline virtual void fire(CommonData* cd) = 0;
    inline  void onCollision(Entity* entity);

protected:
    double health = 400;
};

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
