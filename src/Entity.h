#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "CommonData.h"
#include <cmath>


class Entity{
public:
        Entity(sf::Angle _angle, const std::filesystem::path& _texture, const float _width, const float _height, const float _size, float _x, float _y): angle(_angle), width(_width), height(_height), size(_size), x(_x), y(_y) {
            if (!texture.loadFromFile(_texture)) std::cout<<"Failed to load texture"<<std::endl;

            rectangle.setSize({width*size, height*size});
            rectangle.setTexture(&texture);
        }

        virtual ~Entity(){}
        virtual void update(float deltaTime, CommonData* cd) = 0;
        const sf::RectangleShape& getRectangle(){return rectangle;}

protected:
    sf::Texture texture;
    sf::RectangleShape rectangle;
    float width, height, size;
    float x;
    float y;
    sf::Angle angle = sf::degrees(0);;
    float speed = 0;
    friend class Engine;
    friend class CommonData;
};


#endif //ENTITY_H
