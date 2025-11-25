#ifndef TILEMAP_H
#define TILEMAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>


class TileMap {
public:
  TileMap(int width, int height);
  void generate(int width, int height);
  const std::vector<std::vector<short>>& getTileMap(){return tilelID;}
  short getTileID(const int i, const int j){return tilelID[i][j];}
  sf::Texture& getTiles(const int i, const int j);
  sf::Texture& getTiles(const int num);

protected:
    std::mt19937 generator;
	std::uniform_int_distribution<int> distribution;

    std::vector<std::vector<short>> tilelID;
    std::vector<sf::Texture> tileMap;
};

TileMap::TileMap(const int width,const int height): generator(std::random_device{}()), distribution(1, 8){
	tileMap.resize(8);
    tileMap[0].loadFromFile("background0.png");
    tileMap[1].loadFromFile("background1.png");
    tileMap[2].loadFromFile("background2.png");
    tileMap[3].loadFromFile("background3.png");
    tileMap[4].loadFromFile("Star1.png");
    tileMap[5].loadFromFile("Star2.png");
    tileMap[6].loadFromFile("Star3.png");
    tileMap[7].loadFromFile("Star4.png");

    tilelID.resize(height);
    generate(width, height);
}

void TileMap::generate(const int width, const int height){
	for(int i = 0; i < height; i++){
          tilelID[i].resize(width);
          for(int j = 0; j < width; j++){
            tilelID[i][j] = distribution(generator);
          }
	}
}

sf::Texture& TileMap::getTiles(const int i, const int j){
  return tileMap[tilelID[i][j]];
}

sf::Texture& TileMap::getTiles(const int num){
  return tileMap[num];
}



#endif //TILEMAP_H
