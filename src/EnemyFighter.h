#ifndef ENEMYFIGHTER_H
#define ENEMYFIGHTER_H

#include "SpaceShip.h"


class EnemyFighter: public SpaceShip{
public:
    EnemyFighter(sf::Angle angle, const sf::Texture& texture,  float width,  float height,  float size, const sf::Vector2f& _pos , float  maxSpeed, float _acceleration, float _rotateSpeed);

    inline void update(float deltaTime, CommonData* cd)override;
    inline void fire(CommonData* cd)override;
protected:
    float rotateSpeed;
};

EnemyFighter::EnemyFighter(sf::Angle angle, const sf::Texture& texture, const float width, const float height,
                                    const float size, const sf::Vector2f& _pos , float  maxSpeed, float _acceleration, float _rotateSpeed):
                                    rotateSpeed(_rotateSpeed), SpaceShip( angle, texture, width, height, size, _pos, maxSpeed, _acceleration,enemy) {}

void EnemyFighter::update(float deltaTime, CommonData* cd){
    sf::Vector2f diff  = cd->getPlayerPos() - pos;

    float tmpAngle = std::atan2(diff.y, diff.x);
    angle = sf::degrees(tmpAngle*180.0f/M_PI + 90.0f);

    velocity.x += sin(angle.asRadians())*acceleration*deltaTime*rotateSpeed;
    velocity.y += -cos(angle.asRadians())*acceleration*deltaTime*rotateSpeed;

    const float length = sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
    if (length>maxSpeed) {
        velocity.x = velocity.x*maxSpeed/length;
        velocity.y = velocity.y*maxSpeed/length;
    }

    pos.x += deltaTime*velocity.x;
    pos.y += deltaTime*velocity.y;

    rectangle.setRotation(angle);
    rectangle.setPosition(pos);

    if (!isFire && fireTimer > 1) {
        isFire = true;
        fireTimer = 0.0f;
        fire(cd);
    }else {
        isFire = false;
        fireTimer += deltaTime;
    }
}

void EnemyFighter::fire(CommonData* cd) {

        sf::Vector2f left;
        left.x = pos.x - cos(angle.asRadians())*15;
        left.y = pos.y - sin(angle.asRadians())*15;

        sf::Vector2f right;
        right.x = pos.x + cos(angle.asRadians())*15;
        right.y = pos.y + sin(angle.asRadians())*15;

        cd->get_entities()->push_back(std::make_unique<Bullet>(angle, cd->getObjTexture("enemyBullet"), 1.0f, 3.0f, 4.0f, left, 1500, 1, enemyBullet));
        cd->get_entities()->push_back(std::make_unique<Bullet>(angle, cd->getObjTexture("enemyBullet"), 1.0f, 3.0f, 4.0f, right, 1500, 1, enemyBullet));
}


#endif
