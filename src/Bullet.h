#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet: public Entity {
public:
  Bullet(float  _maxSpeed, sf::Angle _ang, const std::filesystem::path& _texture, const float _width, const float _height, const float _size, float _speed, const sf::Vector2f& _pos, entityType type):
    Entity(_maxSpeed, _ang, _texture, _width, _height, _size, _pos, type), speed(_speed) {

  }

  inline void update(float deltaTime, CommonData* cd) override;
  float getDmg(){ return dmg; }
private:
  float speed;
  float dmg = 10;
};

void Bullet::update(float deltaTime, CommonData* cd){
    velocity.x = sin(angle.asRadians())*maxSpeed;
    velocity.y = -cos(angle.asRadians())*maxSpeed;

    pos.x += deltaTime*velocity.x;
    pos.y += deltaTime*velocity.y;

    rectangle.setRotation(angle);
    rectangle.setPosition(pos);


    //target.x = pos.x + deltaTime*velocity.x;
    //target.y = pos.y + deltaTime*velocity.y;

}

#endif //BULLET_H
