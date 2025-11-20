#ifndef COMMONDATA_H
#define COMMONDATA_H

class Entity;

class CommonData{
public:
    explicit CommonData(std::vector<std::unique_ptr<Entity>>* _entities, float* x, float* y) : playerX(x), playerY(y), entities(_entities){}

    [[nodiscard]] std::vector<std::unique_ptr<Entity>>* get_entities() const {return entities;}
    [[nodiscard]] float getPlayerX() const {return *playerX;}
    [[nodiscard]] float getPlayerY() const {return *playerY;}

protected:
    std::vector<std::unique_ptr<Entity>>* entities;
    float* playerX;
    float* playerY;
};


#endif //COMMONDATA_H
