#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H


#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>

class ResourceManager{
public:
  inline void setTexture(const std::string& name, std::filesystem::path path);
  inline sf::Texture& getTexture(const std::string& name);
protected:
  std::unordered_map<std::string, sf::Texture> textures;
};

void ResourceManager::setTexture(const std::string& name, const std::filesystem::path path){
  sf::Texture tmp;
  bool check = tmp.loadFromFile(path);
  if(!check){
    throw std::runtime_error("invalid path");
  }
  textures[name] = std::move(tmp);
}

sf::Texture& ResourceManager::getTexture(const std::string& name){
  auto it = textures.find(name);
  if (it == textures.end()) {
    throw std::runtime_error("invalid name");
  }
  return it->second;
}

#endif //RESOURCEMANAGER_H
