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

        inline Entity( sf::Angle angle, const sf::Texture& _texture,  float _width,  float _height,  float _size, sf::Vector2f _pos, float _maxSpeed, float _acceleration, entityType _type);
        virtual ~Entity()=default;
        virtual void update(float deltaTime, CommonData* cd) = 0;



//getters
        sf::Vector2f* getPos(){ return &pos;}
        entityType getType()const{ return type; }
        bool getMark()const{ return markToDelete; }
        const sf::RectangleShape& getRectangle(){return rectangle;}

protected:
    sf::Texture texture;
    sf::RectangleShape rectangle;
    sf::Vector2f pos;
    sf::Vector2f velocity = {1, 1};
    sf::Angle angle = sf::degrees(0);;
    float maxSpeed, acceleration;
    bool markToDelete = false;

    entityType type;
    friend class Engine;
    friend class CommonData;
};

Entity::Entity(const sf::Angle _angle, const sf::Texture& _texture, const float width, const float height, const float size,
                const  sf::Vector2f _pos, float _maxSpeed, float acceleration, entityType _type):
                    angle(_angle), pos(_pos), type(_type), maxSpeed(_maxSpeed), acceleration(acceleration), texture(_texture){
    rectangle.setTexture(&texture);
    rectangle.setPosition(pos);
    rectangle.setSize({width*size, height*size});
}


#endif //ENTITY_H
