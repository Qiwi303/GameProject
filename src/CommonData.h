#ifndef COMMONDATA_H
#define COMMONDATA_H

class Entity;

class CommonData{
public:
    explicit CommonData(std::vector<std::unique_ptr<Entity>>* _entities, sf::Vector2f* _playerPos) : playerPos(_playerPos), entities(_entities){}

    [[nodiscard]] std::vector<std::unique_ptr<Entity>>* get_entities() const {return entities;}
    [[nodiscard]] sf::Vector2f getPlayerPos() const {return *playerPos;}

protected:
    std::vector<std::unique_ptr<Entity>>* entities;
    sf::Vector2f* playerPos;
};

#endif //COMMONDATA_H
