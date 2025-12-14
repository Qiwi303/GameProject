#ifndef PLAYER_H
#define PLAYER_H
#include "SpaceShip.h"
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <memory>



class Player: public SpaceShip{
public:
    inline Player(sf::Angle _angle,  const sf::Texture& texture,
                  float width,  float height,  float size, const sf::Vector2f& _pos, float maxSpeed,
                  float acceleration, sf::Angle _rotateSpeed);
    inline void update(float deltaTime, CommonData* cd) override;
    void fire(CommonData* cd) override;


protected:
    float speed = 0.0f;
    float fireTimer = 0.0f;
    bool isPressed = false;
    sf::Angle rotateSpeed;
    friend class Engine;
};

Player::Player(sf::Angle _angle, const sf::Texture& texture,
               const float width, const float height, const float size, const sf::Vector2f& pos,
               const float maxSpeed, const float acceleration, sf::Angle _rotateSpeed):
                 rotateSpeed(_rotateSpeed),  SpaceShip(_angle, texture, width, height, size, pos, maxSpeed, acceleration, player) {
}

void Player::update(const float deltaTime, CommonData* cd) {
    if (isKeyPressed(sf::Keyboard::Scancode::D)){
        angle += rotateSpeed*deltaTime;
    }

    if (isKeyPressed(sf::Keyboard::Scancode::A)){
        angle -= rotateSpeed*deltaTime;
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

    pos.x +=  deltaTime*velocity.x;
    pos.y +=  deltaTime*velocity.y;

    rectangle.setRotation(angle);
    rectangle.setPosition(pos);

    if (isButtonPressed(sf::Mouse::Button::Left) && !isFire && fireTimer > 0.2) {
        isFire = true;
        fireTimer = 0.0f;
        fire(cd);
    }else {
        isFire = false;
        fireTimer += deltaTime;
    }

}

void Player::fire(CommonData* cd){
        sf::Vector2f mousePos = cd->mousePos();
        sf::Vector2f diff = mousePos - pos;
        float mousePlayer = std::atan2(diff.y, diff.x);
        mousePlayer +=  M_PI / 2.0f;
        float angleDiff = mousePlayer - angle.asRadians();

        while (angleDiff > M_PI) angleDiff -= 2 * M_PI;
        while (angleDiff < -M_PI) angleDiff += 2 * M_PI;

        const float maxAng = 0.5f;
        //if (angleDiff > maxAng) angleDiff = maxAng;
        //else if (angleDiff < -maxAng) angleDiff = -maxAng;

        float targetAng = angle.asRadians() + angleDiff;
        sf::Angle bulletAng = sf::radians(targetAng);

        sf::Vector2f left;
        left.x = pos.x - cos(angle.asRadians())*15;
        left.y = pos.y - sin(angle.asRadians())*15;

        sf::Vector2f right;
        right.x = pos.x + cos(angle.asRadians())*15;
        right.y = pos.y + sin(angle.asRadians())*15;
        std::filesystem::path b("bullet.png");

        cd->get_entities()->push_back(std::make_unique<Bullet>(bulletAng, cd->getObjTexture("playerBullet") ,
            1.0f, 3.0f, 4.0f, left, 1500, 1, playerBullet));
        cd->get_entities()->push_back(std::make_unique<Bullet>(bulletAng, cd->getObjTexture("playerBullet"),
            1.0f, 3.0f, 4.0f, right, 1500, 1, playerBullet));
}

#endif //PLAYER_H
