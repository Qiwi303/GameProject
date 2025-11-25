#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Engine.h"
#include "EnemyFighter.h"

#define widthOfWindow 50*96
#define heightWindow 50*96

int main() {
    std::srand(std::time(0));

    std::filesystem::path s ("SpaceFighter.png");

    std::filesystem::path b ("bullet.png");
    Player player(sf::Angle(sf::degrees(0)), b,s, 32.0f, 32.0f, 2.5f, {widthOfWindow/2, heightWindow/2});
    EnemyFighter f(sf::Angle(sf::degrees(0)),  s, 32.0f, 32.0f, 2.5f, {widthOfWindow/2, heightWindow/2});

    Engine engine(player, f, 50, 50);
    engine.startGame();
    return 0;
}
