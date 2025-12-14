#ifndef COLLISION_H
#define COLLISION_H
#include <vector>
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Collision {
public:
  struct Cell{
    std::vector<Entity*> playerBullets;
    std::vector<Entity*> enemyBullets;
    std::vector<Entity*> enemies;
    Entity* player;

  };
  inline Collision(int _cellSize, int _width, int _height);
  inline void setEntity(Entity* entity);
  inline void clearGrid();
  inline void allIntersections();
  inline void enemyXenemy(Cell& cell);
  inline void playerXenemy(Cell& cell);
  inline void enemyXbullet(Cell& cell);
  inline void playerXbullet(Cell& cell);
  inline void possibleIntersection(Cell& cell);

protected:
  std::vector<std::vector<Cell>> grid;
  int cellSize;
};


Collision::Collision(const int _cellSize, const int _width, const int _height): cellSize(_cellSize){
  grid.resize(_height);
  for(auto& x: grid) x.resize(_width);
}

void Collision::setEntity(Entity* entity){
  sf::Vector2f index = {(*(entity->getPos())).x/cellSize, (*(entity->getPos())).y/cellSize};

  if (index.x < 0 || index.x >= grid[0].size() ||
        index.y < 0 || index.y >= grid.size()) {
    return;
        }

  entityType type = entity->getType();
  switch(type) {
    case player:
      grid[index.y][index.x].player = entity;
      break;

    case enemy:
      grid[index.y][index.x].enemies.push_back(entity);
     break;

    case enemyBullet:
      grid[index.y][index.x].enemyBullets.push_back(entity);
      break;

    case playerBullet:
      grid[index.y][index.x].playerBullets.push_back(entity);
      break;
  }
}

void Collision::clearGrid(){
  for(auto& x: grid){
    for(auto& y: x){
      y.playerBullets.clear();
      y.enemyBullets.clear();
      y.enemies.clear();
      y.player = nullptr;
    }
  }
}

void Collision::allIntersections() {
  for (auto& x: grid) {
    for (auto& y:x) {
      possibleIntersection(y);
    }
  }
}

void Collision::possibleIntersection(Cell& cell){
  //if (cell.enemies.size() >= 2) enemyXenemy(cell);
  //if (!cell.player && cell.enemies.size() >= 1)playerXenemy(cell);
  if (!cell.playerBullets.empty() && !cell.enemies.empty()) enemyXbullet(cell);
  if (!cell.enemyBullets.empty() && cell.player!=nullptr) playerXbullet(cell);
}

//void Collision::enemyXenemy(Cell& cell){
//  for (int i = 0; i < cell.enemies.size(); ++i) {
//    for (int j = i + 1; j < cell.enemies.size(); ++j) {
//      sf::FloatRect bound1 = cell.enemies[i]->getRectangle().getGlobalBounds();
//      sf::FloatRect bound2 = cell.enemies[j]->getRectangle().getGlobalBounds();
//      if( bound1.findIntersection(bound2)) {
//        dynamic_cast<SpaceShip*>(cell.enemies[i])->onCollision(cell.enemies[j]);
//        dynamic_cast<SpaceShip*>(cell.enemies[j])->onCollision(cell.enemies[i]);
//      }
//    }
//  }
//}
//
//void Collision::playerXenemy(Cell& cell){
//  sf::FloatRect playerBound = cell.player->getRectangle().getGlobalBounds();
//  for (const auto& x: cell.enemies) {
//    sf::FloatRect enemyBound = x->getRectangle().getGlobalBounds();
//    if( playerBound.findIntersection(enemyBound)) {
//      dynamic_cast<SpaceShip*>(cell.player)->onCollision(x);
//      dynamic_cast<SpaceShip*>(x)->onCollision(cell.player);
//    }
//  }
//}

void Collision::enemyXbullet(Cell& cell){
  for (int i = 0; i < cell.enemies.size(); ++i) {
    for (int j = 0; j < cell.playerBullets.size(); ++j) {
      sf::FloatRect bound1 = cell.enemies[i]->getRectangle().getGlobalBounds();
      sf::FloatRect bound2 = cell.playerBullets[j]->getRectangle().getGlobalBounds();
      if( bound1.findIntersection(bound2)) {
        dynamic_cast<SpaceShip*>(cell.enemies[i])->onCollision(cell.playerBullets[j]);
        dynamic_cast<Bullet*>(cell.playerBullets[j])->setMark();
      }
    }
  }
}

void Collision::playerXbullet(Cell& cell){
  sf::FloatRect playerBound = cell.player->getRectangle().getGlobalBounds();
  for (const auto& x: cell.enemyBullets) {
    sf::FloatRect enemyBound = x->getRectangle().getGlobalBounds();
    if( playerBound.findIntersection(enemyBound)) {
      dynamic_cast<SpaceShip*>(cell.player)->onCollision(x);
      dynamic_cast<Bullet*>(x)->setMark();
    }
  }
}






#endif
