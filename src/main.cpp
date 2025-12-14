#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Engine.h"
#include "EnemyFighter.h"

#define widthOfWindow 50*96
#define heightWindow 50*96

int main() {
    std::srand(std::time(0));

   //std::filesystem::path enemy ("enemy.png");
   //std::filesystem::path b ("bullet.png");
    //std::filesystem::path s ("SpaceFighter.png");
   //Player player(sf::Angle(sf::degrees(0)), s, 32.0f, 32.0f, 2.5f, {widthOfWindow/2, heightWindow/2}, 600, 1000, sf::degrees(4));
   //EnemyFighter f(sf::Angle(sf::degrees(0)),  enemy, 32.0f, 32.0f, 2.5f, {(widthOfWindow - 200 )/2, (heightWindow - 200)/2}, 600, 1000, 0.7);

    Engine engine(50, 50);
    engine.startGame();
    return 0;
}
