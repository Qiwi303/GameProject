#ifndef PLAYER_H
#define PLAYER_H
#include "SpaceShip.h"
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <memory>



class Player: public SpaceShip{
public:
    inline Player(float  maxSpeed, sf::Angle _angle, const std::filesystem::path& _bullet, const std::filesystem::path& texture,  float width,  float height,  float size, const sf::Vector2f& _pos);
    inline void update(float deltaTime, CommonData* cd) override;
    inline void fire(CommonData* cd) override;

protected:
    std::filesystem::path bullet;
    friend class Engine;
    bool isPressed = false;
    bool isFire = false;
    float fireTimer = 0.0f;
    float acceleration = 1000;
};

Player::Player(float  maxSpeed, sf::Angle _angle, const std::filesystem::path& _bullet, const std::filesystem::path& texture, const float width, const float height, const float size, const sf::Vector2f& _pos):
        bullet(_bullet), SpaceShip( maxSpeed, _angle, texture, width, height, size, _pos, player) {

}

void Player::update(const float deltaTime, CommonData* cd) {
    if (isKeyPressed(sf::Keyboard::Scancode::D)){
        angle += sf::degrees(2.5);
    }

    if (isKeyPressed(sf::Keyboard::Scancode::A)){
        angle -= sf::degrees(2.5);
    }

    if(isKeyPressed(sf::Keyboard::Scancode::W)) {
        velocity.x += sin(angle.asRadians())*acceleration*deltaTime;
        velocity.y += -cos(angle.asRadians())*acceleration*deltaTime;
        const float length = sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
        if (length>maxSpeed) {
            velocity.x = velocity.x*maxSpeed/length;
            velocity.y = velocity.y*maxSpeed/length;
        }
    }else {
        velocity.x *= 0.95;
        velocity.y *= 0.95;
    }

    if (isButtonPressed(sf::Mouse::Button::Left) && !isFire && fireTimer > 0.2) {
        isFire = true;
        fireTimer = 0.0f;
        fire(cd);
    }else {
        isFire = false;
        fireTimer += deltaTime;
    }

    pos.x += deltaTime*velocity.x;
    pos.y += deltaTime*velocity.y;

    rectangle.setRotation(angle);
    rectangle.setPosition(pos);
}

void Player::fire(CommonData* cd) {

        sf::Vector2f left;
        left.x = pos.x - cos(angle.asRadians())*15;
        left.y = pos.y - sin(angle.asRadians())*15;

        sf::Vector2f right;
        right.x = pos.x + cos(angle.asRadians())*15;
        right.y = pos.y + sin(angle.asRadians())*15;
        std::filesystem::path b("bullet.png");

        cd->get_entities()->push_back(std::make_unique<Bullet>(1600, angle, b , 1.0f, 3.0f, 4.0f, 1500, left, playerBullet));
        cd->get_entities()->push_back(std::make_unique<Bullet>(1600, angle, b, 1.0f, 3.0f, 4.0f, 1500, right, playerBullet));
}


#endif //PLAYER_H
