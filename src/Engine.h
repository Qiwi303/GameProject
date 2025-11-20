#ifndef ENGINE_H
#define ENGINE_H

#include "SpaceShip.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Player.h"
#include <vector>
#include <memory>
#include "CommonData.h"
#include "EnemyFighter.h"
#include "Render.h"

#define width 1920
#define height 1080



class Engine{
public:
    inline Engine(Player& _player, EnemyFighter& f, int _mapWidthInTiles, int _mapHeigthInTiles);
    inline~Engine();
    void startGame();
    void checkBounds();
    void update(float deltaTime);

protected:
    std::vector<std::unique_ptr<Entity>> entities;
    sf::RenderWindow* window;
    CommonData* commonData;
    Render* render;
    int mapWidthInTiles, mapHeigthInTiles;

};

Engine::Engine(Player& _player, EnemyFighter& f, int _mapWidthInTiles, int _mapHeigthInTiles): mapWidthInTiles(_mapWidthInTiles), mapHeigthInTiles(_mapHeigthInTiles){
    entities.push_back(std::make_unique<Player>(_player));
    entities.push_back(std::make_unique<EnemyFighter>(f));

    window = new  sf::RenderWindow(sf::VideoMode({width, height}), "SFML window");
    window->setFramerateLimit(144);

    commonData = new CommonData(&entities,dynamic_cast<Player*>(entities[0].get())->getX(), dynamic_cast<Player*>(entities[0].get())->getY());
    render = new Render(commonData, window,  mapWidthInTiles, mapHeigthInTiles);
}

Engine::~Engine() {
    delete window;
    delete commonData;
    delete render;
}

void Engine::startGame() {
    sf::Clock clock;

    while (window->isOpen()) {

        float deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
        }

        update(deltaTime);
        checkBounds();
        render->drawGame(entities);
    }
}

void Engine::checkBounds() {
    for(int i = entities.size() - 1; i >= 0; --i) {
        if (entities[i]->x < -100 || entities[i]->x > mapWidthInTiles*96 + 100 || entities[i]->y < -100 || entities[i]->y > mapHeigthInTiles*96 + 100) {
            entities[i] = std::move(entities.back());
            entities.pop_back();
        }
    }
}

void Engine::update(float deltaTime) {
    for (size_t i = 0; i < entities.size(); i++) {
        entities[i]->update(deltaTime, commonData);
    }
}



#endif