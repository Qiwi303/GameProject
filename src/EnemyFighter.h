#ifndef ENEMYFIGHTER_H
#define ENEMYFIGHTER_H

#include "SpaceShip.h"


class EnemyFighter: public SpaceShip{
public:
    EnemyFighter(sf::Angle _angle, const std::filesystem::path& texture, const float width, const float height, const float size, const sf::Vector2f& _pos): SpaceShip( _angle, texture, width, height, size, _pos, enemy) {}

    inline void update(float deltaTime, CommonData* cd)override;
    inline void fire(CommonData* cd)override;
};

void EnemyFighter::update(float deltaTime, CommonData* cd){
    sf::Vector2f diff;
    diff = cd->getPlayerPos() - pos;

    float tmpAngle = std::atan2(diff.y, diff.x);
    sf::Angle angle = sf::degrees(tmpAngle*180.0f/M_PI + 90.0f);

    pos.x += deltaTime*150*sin(angle.asRadians());
    pos.y -= deltaTime*150*cos(angle.asRadians());


    rectangle.setRotation(angle);
    rectangle.setPosition(pos);
}

void EnemyFighter::fire(CommonData* cd){}


#endif
