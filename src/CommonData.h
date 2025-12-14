#ifndef COMMONDATA_H
#define COMMONDATA_H
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class Entity;

class CommonData{
public:
    inline CommonData(ResourceManager& _manager, std::vector<std::unique_ptr<Entity>>* _entities, sf::RenderWindow* _window);

    [[nodiscard]] std::vector<std::unique_ptr<Entity>>* get_entities() const {return entities;}
    [[nodiscard]] sf::Vector2f getPlayerPos() const {return *playerPos;}
    inline sf::Texture& getObjTexture(const std::string& name);
    sf::Vector2f mousePos();
    void setPlayerPos( sf::Vector2f* _playerPos);


protected:
    std::vector<std::unique_ptr<Entity>>* entities;
    sf::Vector2f* playerPos;
    sf::RenderWindow* window;
    ResourceManager manager;

};

CommonData::CommonData(ResourceManager& _manager, std::vector<std::unique_ptr<Entity>>* _entities, sf::RenderWindow* _window):
    manager(_manager), entities(_entities), window(_window){}

sf::Texture& CommonData::getObjTexture(const std::string& name) {
    return manager.getTexture(name);
}

sf::Vector2f CommonData::mousePos() {
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(*window);
    return window->mapPixelToCoords(mousePixelPos);
}

void CommonData::setPlayerPos( sf::Vector2f* _playerPos) {
    playerPos = _playerPos;
}

#endif //COMMONDATA_H
