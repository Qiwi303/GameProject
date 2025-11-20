#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

#define widthOfWindow 1568
#define heightWindow 980

class Bullet: public Entity {
public:
  Bullet(sf::Angle _ang, const std::filesystem::path& _texture, const float _width, const float _height, const float _size, float _speed, float _x, float _y):
    Entity(_ang, _texture, _width, _height, _size, _x, _y), speed(_speed) {

  }

  void update(float deltaTime, CommonData* cd) override;

private:
  float speed;
};

void Bullet::update(float deltaTime, CommonData* cd){
    x += deltaTime*speed*sin(angle.asRadians());
    y -= deltaTime*speed*cos(angle.asRadians());



    rectangle.setRotation(angle);
    rectangle.setPosition({x, y});
}

#endif //BULLET_H
