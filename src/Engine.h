#ifndef ENGINE_H
#define ENGINE_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <vector>
#include <memory>
#include "CommonData.h"
#include "Render.h"
#include "Collision.h"
#include "LvLBuilder.h"
#include "ResourceManager.h"

#define width 1920
#define height 1080

#define widthOfWindow 50*96
#define heightWindow 50*96


class Engine{
public:
    inline Engine(int _mapWidthInTiles, int _mapHeigthInTiles);
    inline ~Engine();
    void startGame();
    void checkBounds();
    void update(float deltaTime);
    void checkMark();
    void setEntitiesForGrid();
    void setTextures();

protected:
    std::vector<std::unique_ptr<Entity>> entities;
    sf::RenderWindow* window;
    CommonData* commonData;
    Render* render;
    Collision* coll;
    LvLBuilder* lvlBuilder;
    ResourceManager* manager;
    int mapWidthInTiles, mapHeightInTiles;

};

Engine::Engine(const int _mapWidthInTiles, const int _mapHeightInTiles): mapWidthInTiles(_mapWidthInTiles), mapHeightInTiles(_mapHeightInTiles){
    window = new  sf::RenderWindow(sf::VideoMode({width, height}), "SFML window");
    window->setFramerateLimit(60);

    manager = new ResourceManager();
    setTextures();
    commonData = new CommonData(*manager, &entities, window);
    lvlBuilder = new LvLBuilder(*manager, commonData, {100}, 2000, {widthOfWindow/2, heightWindow/2});
    lvlBuilder->SpawnPlayer();
    commonData->setPlayerPos(entities[0]->getPos());
    render = new Render(commonData, window,  mapWidthInTiles, mapHeightInTiles);
    coll = new Collision(48, 100, 100);
    std::cout<<(commonData->getPlayerPos()).x<<" "<<commonData->getPlayerPos().y<<std::endl;
}

Engine::~Engine() {
    delete window;
    delete commonData;
    delete render;
    delete coll;
    delete lvlBuilder;
    delete manager;
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
//спавним врагов
        lvlBuilder->SpawnEnemy();
//Обновляем координаты
        update(deltaTime);
//Заполняем сетку
        setEntitiesForGrid();
//Проверям пересечения
        coll->allIntersections();
//Проверяем Объекты на удаление
        checkMark();
//Проверяем Границу
        checkBounds();
//рисуем
        render->drawGame(entities);
//очищаем сетку
        coll->clearGrid();
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
            if ((*it)->getType() == enemy) {
                lvlBuilder->decEnemy();
            }
            it = entities.erase(it);
        } else {
            ++it;
        }
    }
}
void Engine::update(float deltaTime) {
    for (size_t i = 0; i < entities.size(); i++) {
        entities[i]->update(deltaTime, commonData);
    }
}

void Engine::setEntitiesForGrid() {
    for (const auto& x: entities) {
        coll->setEntity(x.get());
    }
}

void Engine::setTextures() {
    manager->setTexture("player", "SpaceFighter.png");
    manager->setTexture("enemy", "enemy.png");
    manager->setTexture("playerBullet", "bullet.png");
    manager->setTexture("enemyBullet", "enemyBullet.png");
}


#endif