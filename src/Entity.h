#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "CommonData.h"

enum entityType {
    player,
    enemy,
    playerBullet,
    enemyBullet
};

class Entity{
public:
        inline Entity(float _maxSpeed, sf::Angle _angle, const std::filesystem::path& _texture,  float _width,  float _height,  float _size, const sf::Vector2f& _pos, entityType _type);
        virtual ~Entity(){}
        virtual void update(float deltaTime, CommonData* cd) = 0;
        const sf::RectangleShape& getRectangle(){return rectangle;}
        sf::Vector2f* getPos(){ return &pos;}
        sf::Vector2f getTarget(){ return target;}
        entityType getType()const{ return type; }
        bool getMark()const{ return markToDelete; }
        void move();
        //virtual void onCollision(Entity *entity);
        float getRadius(){ return radius;}
        float getMass(){ return mass; }
        sf::Vector2f getVelocity(){ return velocity; }
        void setMark(){ markToDelete = true;}

protected:
    sf::Texture texture;
    sf::RectangleShape rectangle;
    float width, height, size, maxSpeed, radius;
    float mass;
    sf::Vector2f pos, prevPos, target;
    sf::Vector2f velocity = {1,1};
    sf::Angle angle = sf::degrees(0);
    bool markToDelete = false;

    entityType type;
    friend class Engine;
    friend class CommonData;
};

Entity::Entity(float _maxSpeed, sf::Angle _angle, const std::filesystem::path& _texture, const float _width, const float _height, const float _size, const sf::Vector2f& _pos, entityType _type):
    maxSpeed(_maxSpeed), angle(_angle), width(_width), height(_height), size(_size), pos(_pos), type(_type) {
    rectangle.setPosition(pos);
    if (!texture.loadFromFile(_texture)) std::cout<<"Failed to load texture"<<std::endl;

    rectangle.setSize({width*size, height*size});
    rectangle.setTexture(&texture);
}

void Entity::move() {
    rectangle.setPosition(pos);
    rectangle.setRotation(angle);
}

#endif //ENTITY_H
