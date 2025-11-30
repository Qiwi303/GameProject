#ifndef ENEMYFIGHTER_H
#define ENEMYFIGHTER_H

#include "SpaceShip.h"


class EnemyFighter: public SpaceShip{
public:
    EnemyFighter(float _maxSpeed, sf::Angle _angle, const std::filesystem::path& texture, const float width, const float height, const float size, const sf::Vector2f& _pos): SpaceShip(_maxSpeed, _angle, texture, width, height, size, _pos, enemy) {}

    inline void update(float deltaTime, CommonData* cd)override;
    inline void fire(CommonData* cd)override;
protected:
    float maxSpeed = 150;
    float acceleration = 1000;
};

void EnemyFighter::update(float deltaTime, CommonData* cd){
    sf::Vector2f diff;
    diff = cd->getPlayerPos() - pos;
    float length = sqrt(diff.x*diff.x + diff.y*diff.y);
    if(length){
        velocity.x = diff.x*maxSpeed/length;
        velocity.y = diff.y*maxSpeed/length;
    }else {
        velocity = {0.f, 0.f};
    }
    float tmpAngle = std::atan2(diff.y, diff.x);
    sf::Angle angle = sf::degrees(tmpAngle*180.0f/M_PI + 90.0f);

    pos.x += deltaTime*velocity.x;
    pos.y += deltaTime*velocity.y;


    rectangle.setRotation(angle);
    rectangle.setPosition(pos);

    target.x = pos.x + deltaTime*velocity.x;
    target.y = pos.y + deltaTime*velocity.y;

}

void EnemyFighter::fire(CommonData* cd){}


#endif
