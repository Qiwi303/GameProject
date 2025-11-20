#ifndef ENEMYFIGHTER_H
#define ENEMYFIGHTER_H

#include "SpaceShip.h"

#define widthOfWindow 1568.0f
#define heightWindow 980.0f

class EnemyFighter: public SpaceShip{
public:
    EnemyFighter(sf::Angle _angle, const std::filesystem::path& texture,  float width,  float height,  float size, float _x, float _y): SpaceShip( _angle, texture, width, height, size, _x, _y) {}

    inline void update(float deltaTime, CommonData* cd)override;
    inline void fire(CommonData* cd)override;
};

void EnemyFighter::update(float deltaTime, CommonData* cd){
    float dx = cd->getPlayerX() - x;
    float dy = cd->getPlayerY() - y;
    float tmpAngle = std::atan2(dy, dx);
    sf::Angle angle = sf::degrees(tmpAngle*180.0f/M_PI + 90.0f);

    x += deltaTime*150*sin(angle.asRadians());
    y -= deltaTime*150*cos(angle.asRadians());


    rectangle.setRotation(angle);
    rectangle.setPosition({x, y});
}

void EnemyFighter::fire(CommonData* cd){}


#endif
