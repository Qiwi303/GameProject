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

    Player player(600, sf::Angle(sf::degrees(0)), b,s, 64.0f, 64.0f, 1.f, {widthOfWindow/2, heightWindow/2});
    EnemyFighter f(150, sf::Angle(sf::degrees(0)),  s, 64.0f, 64.0f, 1.f, {(widthOfWindow - 100)/2, (heightWindow - 100)/2});

    Engine engine(player, f, 50, 50);
    engine.startGame();
    return 0;
}
