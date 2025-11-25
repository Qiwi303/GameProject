#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet: public Entity {
public:
  Bullet(sf::Angle _ang, const std::filesystem::path& _texture, const float _width, const float _height, const float _size, float _speed, const sf::Vector2f& _pos, entityType type):
    Entity(_ang, _texture, _width, _height, _size, _pos, type), speed(_speed) {

  }
  void setMark(){ markToDelete = true;}
  void update(float deltaTime, CommonData* cd) override;
  float getDmg(){ return dmg; }
private:
  float speed;
  float dmg = 10;
};

void Bullet::update(float deltaTime, CommonData* cd){
    pos.x += deltaTime*speed*sin(angle.asRadians());
    pos.y -= deltaTime*speed*cos(angle.asRadians());

    rectangle.setRotation(angle);
    rectangle.setPosition(pos);
}

#endif //BULLET_H
