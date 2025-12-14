#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet: public Entity {
public:
  inline Bullet(sf::Angle ang, const sf::Texture& texture,  float width,  float height,  float size, sf::Vector2f& pos,  float  maxSpeed, float acceleration, entityType type);
  void setMark() { markToDelete = true;}
  void update(float deltaTime, CommonData* cd) override;
  float getDmg() { return dmg; }
private:
  float speed;
  float dmg = 20;
};

void Bullet::update(float deltaTime, CommonData* cd){
    pos.x += deltaTime*maxSpeed*sin(angle.asRadians());
    pos.y -= deltaTime*maxSpeed*cos(angle.asRadians());

    rectangle.setRotation(angle);
    rectangle.setPosition(pos);
}

Bullet::Bullet(sf::Angle ang, const sf::Texture& texture, const float width, const float height, const float size,
                 sf::Vector2f& pos, const float  maxSpeed, const float acceleration, entityType type):
                    Entity(ang, texture, width, height, size, pos, maxSpeed, acceleration, type){}

#endif //BULLET_H
