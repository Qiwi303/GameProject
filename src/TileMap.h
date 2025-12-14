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

TileMap::TileMap(const int width,const int height): generator(std::random_device{}()), distribution(1, 20){
	tileMap.resize(20);
    tileMap[0].loadFromFile("tile-1.png");
    tileMap[1].loadFromFile("tile-2.png");
    tileMap[2].loadFromFile("tile-3.png");
    tileMap[3].loadFromFile("tile-4.png");
    tileMap[4].loadFromFile("tile-5.png");
    tileMap[5].loadFromFile("tile-6.png");
    tileMap[6].loadFromFile("tile-7.png");
    tileMap[7].loadFromFile("tile-8.png");
    tileMap[8].loadFromFile("tile-9.png");
    tileMap[9].loadFromFile("tile-10.png");
    tileMap[10].loadFromFile("tile-11.png");
    tileMap[11].loadFromFile("tile-12.png");
    tileMap[12].loadFromFile("tile-13.png");
    tileMap[13].loadFromFile("tile-14.png");
    tileMap[14].loadFromFile("tile-15.png");
    tileMap[15].loadFromFile("tile-16.png");
    tileMap[16].loadFromFile("tile-17.png");
    tileMap[17].loadFromFile("tile-18.png");
    tileMap[18].loadFromFile("tile-19.png");
    tileMap[19].loadFromFile("tile-20.png");

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
