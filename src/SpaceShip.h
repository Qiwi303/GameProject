#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Entity.h"
#include "Bullet.h"

class SpaceShip: public Entity{
public:
    SpaceShip(float _maxSpeed, sf::Angle _angle, const std::filesystem::path& texture, const float width, const float height, const float size, const sf::Vector2f& _pos, entityType type ): Entity(_maxSpeed, _angle, texture, width, height, size, _pos, type) {
        float centerX = rectangle.getGeometricCenter().x;
        float centerY = rectangle.getGeometricCenter().y*1.25f;
        rectangle.setOrigin({centerX, centerY});
        mass = 1;
        radius = 32;
    }

    void takeDmg(float dmg);
    inline virtual void fire(CommonData* cd) = 0;
    inline void onCollision(Entity* entity);
    inline void pushAway(Entity* entity);

protected:
    double health = 50;
};

void SpaceShip::onCollision(Entity* entity){
    if ((type == enemy && entity->getType() == playerBullet) ||
            (type == player && entity->getType() == enemyBullet)){
        takeDmg(dynamic_cast<Bullet*>(entity)->getDmg());
        entity->setMark();
    }
    else if (type == player || type == enemy) {
        pushAway(entity);
    }
}

void SpaceShip::takeDmg(const float dmg) {
    if (health - dmg > 0) health -= dmg;
    else markToDelete = true;
}

void SpaceShip::pushAway(Entity* entity) {
    sf::Vector2f direction = pos - *entity->getPos();
    float distance = std::sqrt(direction.x*direction.x + direction.y*direction.y);
    if (distance < 0.001f) {
        direction = sf::Vector2f(1.0f, 0.0f);
        distance = 0.001f;
    }

    direction /= distance;

    float overlap = (radius + entity->getRadius()) - distance;
    float totalMass = mass + entity->getMass();
    float push = overlap * (entity->getMass()/totalMass);
    pos += direction * push;

    float relativeVel = (velocity.x - entity->getVelocity().x)*direction.x +
                        (velocity.y - entity->getVelocity().y)*direction.y;

    if (relativeVel < 0) {
        sf::Vector2f impuls = direction * relativeVel;
        velocity -= impuls*(entity->getMass() / totalMass);
    }


}

#endif //SPACESHIP_H
