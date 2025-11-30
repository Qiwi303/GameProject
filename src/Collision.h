#ifndef COLLISION_H
#define COLLISION_H
#include <vector>
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

class Collision {
protected:
    struct Node {
      Node* left;
      Node* right;
      Entity* ent;
      sf::FloatRect bound;
      explicit Node(Node* _left, Node* _right, Entity* _ent,  sf::FloatRect _bound): left(_left), right(_right), ent(_ent), bound(_bound){}
    };
    Node* root;
    sf::FloatRect mapBounds;
public:
  Collision(sf::FloatRect _mapBounds);
  ~Collision();
  Node* buildBVH(std::vector<Entity*>& entities, sf::FloatRect bounds);
  sf::FloatRect findBounds(std::vector<Entity*>& ents);
  void intersectionSearch(Node* root, Entity* ent);
  void clearBVH(Node* root);
  void setBVH(std::vector<std::unique_ptr<Entity>>& entities);
  void startSearch(Entity* ent);
};

Collision::Collision(const sf::FloatRect _mapBounds): mapBounds(_mapBounds), root(nullptr){}

Collision::~Collision() {
  clearBVH(root);
}

sf::FloatRect Collision::findBounds(std::vector<Entity*>& ents) {
  if (ents.empty()) return sf::FloatRect();

  sf::Vector2f firstPos = *ents[0]->getPos();
  float minX = firstPos.x, maxX = firstPos.x;
  float minY = firstPos.y, maxY = firstPos.y;

  for (auto& ent: ents) {
    sf::Vector2f pos = *ent->getPos();
    if (minX > pos.x) minX = pos.x;
    if (minY > pos.y) minY = pos.y;
    if (maxX < pos.x) maxX = pos.x;
    if (maxY< pos.y) maxY = pos.y;
  }

  return sf::FloatRect({minX, minY},{maxX - minX,  maxY - minY});
}

Collision::Node* Collision::buildBVH(std::vector<Entity*>& ents, sf::FloatRect bounds) {
  if (ents.empty()) return nullptr;
  if (ents.size() == 1) return new Node(nullptr, nullptr, ents[0], ents[0]->getRectangle().getGlobalBounds());

  if (bounds.size.x >= bounds.size.y) {
    std::sort(ents.begin(), ents.end(),
    [](Entity* a, Entity* b)
    {
        return a->getPos()->x < b->getPos()->x;
    });
  }else {
    std::sort(ents.begin(), ents.end(),
    [](Entity* a, Entity* b)
    {
        return a->getPos()->y < b->getPos()->y;
    });
  }


  int mid  = ents.size()/2;

  std::vector left(ents.begin(), ents.begin() + mid);
  sf::FloatRect boundL = findBounds(left);


  std::vector right(ents.begin() + mid, ents.end());
  sf::FloatRect boundR = findBounds(right);
  return new Node(buildBVH(left, boundL),  buildBVH(right, boundR), nullptr, bounds);
}

void Collision::intersectionSearch(Node* root, Entity* ent) {
  if (root == nullptr) return;
  if(ent->getRectangle().getGlobalBounds().findIntersection(root->bound)) {
    if (root->ent != nullptr && root->ent != ent) {
      dynamic_cast<SpaceShip*>(ent)->onCollision(root->ent);
    }
    else {
      intersectionSearch(root->left, ent);
      intersectionSearch(root->right, ent);
    }
  }
}

void Collision::clearBVH(Node* node) {
  if (node == nullptr ) return;
  clearBVH(node->left);
  clearBVH(node->right);
  delete node;
}

void Collision::setBVH(std::vector<std::unique_ptr<Entity>>& entities) {
  std::vector<Entity*> ents;
  for (auto& ent: entities) {
    ents.push_back(ent.get());
  }
  clearBVH(root);
  root = buildBVH(ents, mapBounds);
}

  void Collision::startSearch(Entity* ent) {
    if (ent->getType() == enemy || ent->getType() == player) {
      std::cout<<std::to_string(ent->getType())<<std::endl;
      intersectionSearch(root, ent);
    }
  }



/*class Collision {
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
  //inline void allIntersections();
  inline void enemyXship(Cell& cell, Entity* ent);
  inline void playerXenemy(Cell& cell, Entity* ent);
  inline void enemyXbullet(Cell& cell, Entity* ent);
  inline void playerXbullet(Cell& cell, Entity* ent);
  inline void possibleIntersection(Entity* ent);
  inline bool checkIntersection(Entity* ent1, Entity* ent2);
  inline void setNewEntityPos(Entity* entity);
  inline void deleteElement(Entity* entity, std::vector<Entity*>& entities);
protected:
  std::vector<std::vector<Cell>> grid;
  int cellSize;
  float SpaceShipRadius = 32.f;
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

//void Collision::allIntersections() {
//  for (auto& x: grid) {
//    for (auto& y:x) {
//      possibleIntersection(y);
//    }
//  }
//}

void Collision::possibleIntersection(Entity* ent){

  int targetX = static_cast<int>(ent->getTarget().x / cellSize);
  int targetY = static_cast<int>(ent->getTarget().y / cellSize);

  if (targetX < 0 || targetX >= grid[0].size() ||
      targetY < 0 || targetY >= grid.size()) {
    return;
      }

  Cell cell = grid[targetY][targetX];
  if (!cell.enemies.empty() && ent->getType() == player)playerXenemy(cell, ent);
  if ((cell.enemies.size() >= 2 || !cell.enemies.empty() && cell.player != nullptr) && ent->getType() == enemy) enemyXship(cell, ent);
  if (!cell.enemies.empty() && ent->getType() == playerBullet) enemyXbullet(cell,  ent);
  if (cell.player!=nullptr && ent->getType() == enemyBullet) playerXbullet(cell,  ent);
}

void Collision::playerXenemy(Cell& cell, Entity* player){
  for (auto const enemy: cell.enemies) {

    if (checkIntersection(player, enemy)) {
      dynamic_cast<SpaceShip*>(player)->onCollision(enemy);
    }
  }
}

void Collision::enemyXship(Cell& cell, Entity* currEnemy){
  for (auto const enemy: cell.enemies) {
    if (enemy == currEnemy) continue;
    if (checkIntersection(currEnemy, enemy)) {
      dynamic_cast<SpaceShip*>(currEnemy)->onCollision(enemy);
    }
  }
  if(cell.player != nullptr && checkIntersection(currEnemy, cell.player)) {
    dynamic_cast<SpaceShip*>(currEnemy)->onCollision(cell.player);
  }
}

void Collision::enemyXbullet(Cell& cell, Entity* PlayerBullet){
  sf::FloatRect bulletBound = PlayerBullet->getRectangle().getGlobalBounds();
  for (auto& enemy: cell.enemies) {
    sf::FloatRect enemyBound = enemy->getRectangle().getGlobalBounds();
    if (enemyBound.findIntersection(bulletBound)) {
       dynamic_cast<SpaceShip*>(enemy)->onCollision(PlayerBullet);
    }
  }
}

void Collision::playerXbullet(Cell& cell, Entity* EnemyBullet){
  sf::FloatRect bulletBound = EnemyBullet->getRectangle().getGlobalBounds();
  sf::FloatRect PlayerBound = cell.player->getRectangle().getGlobalBounds();
  if (PlayerBound.findIntersection(bulletBound)) {
    dynamic_cast<SpaceShip*>(cell.player)->onCollision(EnemyBullet);
  }
}

bool Collision::checkIntersection(Entity* ent1, Entity* ent2) {
 sf::Vector2f diff = *ent2->getPos() -  *(ent1->getPos());
 float length = sqrt(diff.x*diff.x + diff.y*diff.y);
 if (length <= SpaceShipRadius*2) return true;
 return false;
}

void Collision::setNewEntityPos(Entity* entity) {
  Cell* oldCell = &grid[(*entity->getPos()).y/cellSize][(*entity->getPos()).x/cellSize];
  entityType type = entity->getType();
  switch(type) {
    case player:
      oldCell->player = nullptr;
    break;

    case enemy:
      deleteElement(entity, oldCell->enemies);
    break;

    case enemyBullet:
      deleteElement(entity, oldCell->enemyBullets);
    break;

    case playerBullet:
      deleteElement(entity, oldCell->playerBullets);
    break;
  }
}

void Collision::deleteElement(Entity* entity, std::vector<Entity*>& entities){
  for (auto it = entities.begin(); it != entities.end(); ++it) {
    if (*it == entity) {
      entities.erase(it);
      return;
    }
  }
}*/










#endif
