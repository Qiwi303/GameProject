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
#include "Collision.h"

#define width 1920
#define height 1080



class Engine{
public:
    inline Engine(Player& _player, EnemyFighter& f, int _mapWidthInTiles, int _mapHeigthInTiles);
    inline ~Engine();
    void startGame();
    void checkBounds();
    void update(float deltaTime);
    void checkMark();
    void checkCollision();

protected:
    std::vector<std::unique_ptr<Entity>> entities;
    sf::RenderWindow* window;
    CommonData* commonData;
    Render* render;
    Collision* coll;
    float mapWidthInTiles, mapHeightInTiles;
};

Engine::Engine(Player& _player, EnemyFighter& f, const int _mapWidthInTiles, const int _mapHeightInTiles): mapWidthInTiles(_mapWidthInTiles), mapHeightInTiles(_mapHeightInTiles){
    entities.push_back(std::make_unique<Player>(_player));
    entities.push_back(std::make_unique<EnemyFighter>(f));

    window = new  sf::RenderWindow(sf::VideoMode({width, height}), "SFML window");
    window->setFramerateLimit(60);

    commonData = new CommonData(&entities, entities[0]->getPos());
    render = new Render(commonData, window,  mapWidthInTiles, mapHeightInTiles);

    sf::FloatRect globalBound({0, 0}, {mapWidthInTiles * 96, mapHeightInTiles * 96});
    coll = new Collision(globalBound);
}

Engine::~Engine() {
    delete window;
    delete commonData;
    delete render;
    delete coll;
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
//Заполняем дерево
        coll->setBVH(entities);
//Обновляем координаты
        update(deltaTime);
//проверяем на коллизии
        checkCollision();
//Проверяем Объекты на удаление
        checkMark();
//Проверяем Границу
        checkBounds();
//рисуем
        render->drawGame(entities);
    }
}

void Engine::checkBounds() {
    for(int i = entities.size() - 1; i >= 0; --i) {
        if (entities[i]->pos.x < -100 || entities[i]->pos.x > mapWidthInTiles*96 + 100 || entities[i]->pos.y < -100 || entities[i]->pos.y > mapHeightInTiles*96 + 100) {
            entities[i] = std::move(entities.back());
            entities.pop_back();
        }
    }
}

void Engine::checkMark(){
    for (auto it = entities.begin(); it!=entities.end();) {
        if ((*it)->getMark()) {
            it = entities.erase(it);
        } else {
            ++it;
        }
    }
}
void Engine::update(float deltaTime) {
    for(size_t i = 0; i < entities.size(); i++) {
        entities[i]->update(deltaTime, commonData);
    }
}

void Engine::checkCollision() {
    for (auto& ent: entities) {
            coll->startSearch(ent.get());
    }
}

#endif