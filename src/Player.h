#ifndef PLAYER_H
#define PLAYER_H
#include "SpaceShip.h"
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <memory>

#define widthOfWindow 1568
#define heightWindow 980

class Player: public SpaceShip{
public:
    inline Player(sf::Angle _angle, const std::filesystem::path& _bullet, const std::filesystem::path& texture,  float width,  float height,  float size, float _x, float _y);
    inline void update(float deltaTime, CommonData* cd) override;
    void fire(CommonData* cd) override;
    float* getX() { return &x; }
    float* getY() { return &y; }


protected:
    std::filesystem::path bullet;
    float speed = 0;
    friend class Engine;
    bool isPressed = false;
    bool isFire = false;
    float fireTimer = 0.0f;
};

Player::Player(sf::Angle _angle, const std::filesystem::path& _bullet, const std::filesystem::path& texture, const float width, const float height, const float size, float _x, float _y):
        bullet(_bullet), SpaceShip(_angle, texture, width, height, size, _x, _y) {

}

void Player::update(const float deltaTime, CommonData* cd) {
    if (isKeyPressed(sf::Keyboard::Scancode::D)){
        angle += sf::degrees(5);
    }

    if (isKeyPressed(sf::Keyboard::Scancode::A)){
        angle -= sf::degrees(5);
    }

    if(isKeyPressed(sf::Keyboard::Scancode::W)) {
        if (speed < 500) speed+=50.f;

    }
    else if (speed > 0) {
        speed -= 10.0f;
        isPressed = true;
    }else {
        isPressed = false;
    }

    if (isButtonPressed(sf::Mouse::Button::Left) && !isFire && fireTimer > 0.2) {
        isFire = true;
        fireTimer = 0.0f;
        fire(cd);
    }else {
        isFire = false;
        fireTimer += deltaTime;
    }

    x += deltaTime*speed*sin(angle.asRadians());
    y -= deltaTime*speed*cos(angle.asRadians());

    rectangle.setRotation(angle);
    rectangle.setPosition({x, y});
}

void Player::fire(CommonData* cd) {

        float xLeft = x - cos(angle.asRadians())*15;
        float yLeft = y - sin(angle.asRadians())*15;

        float xRight = x + cos(angle.asRadians())*15;
        float yRight = y + sin(angle.asRadians())*15;
        std::filesystem::path b("bullet.png");

        cd->get_entities()->push_back(std::make_unique<Bullet>(angle, b , 1.0f, 3.0f, 4.0f, 1500, xLeft, yLeft));
        cd->get_entities()->push_back(std::make_unique<Bullet>(angle, b, 1.0f, 3.0f, 4.0f, 1500, xRight, yRight));
}

#endif //PLAYER_H
