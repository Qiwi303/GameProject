#ifndef LVLBUILDER_H
#define LVLBUILDER_H
#include <vector>
#include "enemyFighter.h"
#include "Player.h"
#include "ResourceManager.h"

#define widthOfWindow 50*96
#define heightWindow 50*96

class LvLBuilder{
public:
    LvLBuilder(ResourceManager& _manager, CommonData* cd, const std::vector<int>& maxEnemyCount, float _spawnDist, sf::Vector2f playerInitialPos);
    sf::Vector2f getSpawnPos();

    void SpawnEnemy();
    void SpawnPlayer();

    void decEnemy(){currentEnemyCount[0]--;}


protected:
    ResourceManager& manager;
    std::vector<int> maxEnemyCount;
    std::vector<int> currentEnemyCount;
    float spawnDist;
    CommonData* cd;


    std::filesystem::path enemy;
};

LvLBuilder::LvLBuilder(ResourceManager& _manager, CommonData* _cd, const std::vector<int>& _maxEnemyCount, float _spawnDist, sf::Vector2f playerInitialPos):
                                       manager(_manager), maxEnemyCount(_maxEnemyCount), spawnDist(_spawnDist), cd(_cd){
    currentEnemyCount.resize(maxEnemyCount.size());
}

sf::Vector2f LvLBuilder::getSpawnPos(){
    float randomDegrees = static_cast<float>(std::rand() % 360);
    float randomRadians = randomDegrees * 3.14159f / 180.0f;
    float x = spawnDist*sin(randomRadians);
    float y = -1*spawnDist*cos(randomRadians);
    return {x + cd->getPlayerPos().x, y + cd->getPlayerPos().y};
}

void LvLBuilder::SpawnEnemy(){
    if(currentEnemyCount[0] < maxEnemyCount[0]){
        cd->get_entities()->push_back(
           std::make_unique<EnemyFighter>(
               sf::Angle(sf::degrees(0)),
               manager.getTexture("enemy"),
               32.0f, 32.0f, 2.5f,
               getSpawnPos(),
               600, 1000, 0.7
           ));
        currentEnemyCount[0]++;
    }
}

void LvLBuilder::SpawnPlayer() {
    sf::Vector2f pos = {widthOfWindow/2.f, heightWindow/2.f};
    cd->get_entities()->push_back(
           std::make_unique<Player>(
               sf::Angle(sf::degrees(0)),
               manager.getTexture("player"),
               32.0f, 32.0f, 2.5f,
               pos,
               600, 1000, sf::degrees(300)
           ));
}

#endif //LVLBUILDER_H
