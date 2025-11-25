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
        inline Entity(sf::Angle _angle, const std::filesystem::path& _texture,  float _width,  float _height,  float _size, const sf::Vector2f& _pos, entityType _type);
        virtual ~Entity(){}
        virtual void update(float deltaTime, CommonData* cd) = 0;
        const sf::RectangleShape& getRectangle(){return rectangle;}
        sf::Vector2f* getPos(){ return &pos;}
        entityType getType()const{ return type; }
        bool getMark()const{ return markToDelete; }

protected:
    sf::Texture texture;
    sf::RectangleShape rectangle;
    float width, height, size;
    sf::Vector2f pos;
    sf::Angle angle = sf::degrees(0);;
    float speed = 0;
    bool markToDelete = false;

    entityType type;
    friend class Engine;
    friend class CommonData;
};

Entity::Entity(sf::Angle _angle, const std::filesystem::path& _texture, const float _width, const float _height, const float _size, const sf::Vector2f& _pos, entityType _type):
    angle(_angle), width(_width), height(_height), size(_size), pos(_pos), type(_type) {
    rectangle.setPosition(pos);
    if (!texture.loadFromFile(_texture)) std::cout<<"Failed to load texture"<<std::endl;

    rectangle.setSize({width*size, height*size});
    rectangle.setTexture(&texture);
}


#endif //ENTITY_H
