#ifndef RENDER_H
#define RENDER_H

#include "TileMap.h"
#include "CommonData.h"
#include "Entity.h"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics.hpp>

class Render {
public:
  Render(CommonData* _commonData, sf::RenderWindow* _window, int _mapWidthInTiles, int _mapHeightInTiles);
  ~Render(){ delete tileMap; }
  void drawGame(const std::vector<std::unique_ptr<Entity>>& entities);
  void drawTileMap();
  void drawEntities(const std::vector<std::unique_ptr<Entity>>& _entities);
protected:
    TileMap* tileMap;
    CommonData* commonData;
    sf::RenderWindow* window;
    sf::View camera;
    sf::Texture finalAtlas;
    sf::VertexArray quad;

    float cameraWidth = 1920.f;
    float cameraHeight = 1080.f;
    unsigned tileSize = 96;
    int mapWidthInTiles, mapHeightInTiles;
};

Render::Render(CommonData* _commonData, sf::RenderWindow* _window, int _mapWidthInTiles, int _mapHeightInTiles): commonData(_commonData),
    window(_window), mapWidthInTiles(_mapWidthInTiles), mapHeightInTiles(_mapHeightInTiles) {
    tileMap = new TileMap(mapWidthInTiles, _mapHeightInTiles);
    sf::RenderTexture atlas;
    atlas.resize({tileSize*20,tileSize});
    quad.setPrimitiveType(sf::PrimitiveType::Triangles);
    quad.resize(50*50*6);
    camera.setSize({cameraWidth, cameraHeight});


    int k = 0;
    for (int i = 0; i < mapHeightInTiles; i++) {
        for (int j = 0; j < mapWidthInTiles; j++) {
          	int tileID = tileMap->getTileID(i,j);

            quad[k].position = sf::Vector2f({j*tileSize*1.f, i*tileSize*1.f});
            quad[k++].texCoords = {(tileID-1)*tileSize*1.f, 0.f};
            quad[k].position = sf::Vector2f({(j+1)*tileSize*1.f, i*96.f});
			quad[k++].texCoords = {(tileID)*tileSize*1.f, 0.f};
            quad[k].position = sf::Vector2f({j*tileSize*1.f, (i+1)*tileSize*1.f});
			quad[k++].texCoords = {(tileID-1)*tileSize*1.f, tileSize*1.f};

            quad[k].position = sf::Vector2f({j*tileSize*1.f, (i+1)*tileSize*1.f});
            quad[k++].texCoords = {(tileID-1)*tileSize*1.f, tileSize*1.f};
            quad[k].position = sf::Vector2f({(j+1)*tileSize*1.f, (i+1)*tileSize*1.f});
            quad[k++].texCoords = {tileID*tileSize*1.f, tileSize*1.f};
            quad[k].position = sf::Vector2f({(j+1)*tileSize*1.f, i*tileSize*1.f});
            quad[k++].texCoords = {tileID*tileSize*1.f, 0.f};
        }
    }

  	atlas.clear();
	for(int i = 0; i < 20; ++i){
  		sf::Sprite tmp(tileMap->getTiles(i));
        tmp.setPosition({i*tileSize*1.f, 0.f});
        atlas.draw(tmp);
    }

    atlas.display();
    sf::Image atlasImage = atlas.getTexture().copyToImage();
    finalAtlas.loadFromImage(atlasImage);
}

void Render::drawEntities(const std::vector<std::unique_ptr<Entity>>& entities){
    for(const auto& ent : entities){
        window->draw(ent->getRectangle());
    }
}

void Render::drawTileMap(){
	sf::RenderStates states;
	states.texture = &finalAtlas;
	window->draw(quad, states);
}

void Render::drawGame(const std::vector<std::unique_ptr<Entity>>& entities){
    window->clear();

    sf::Vector2f pos = commonData->getPlayerPos();
    if (pos.x - cameraWidth/2 <= 0 || pos.x + cameraWidth/2 >= mapWidthInTiles*tileSize) {
        pos.x = camera.getCenter().x;
    }
    if (pos.y - cameraHeight/2 <= 0 || pos.y + cameraHeight/2 >= mapHeightInTiles*tileSize) {
        pos.y = camera.getCenter().y;
    }
    camera.setCenter(pos);

    window->setView(camera);
    drawTileMap();
    drawEntities(entities);
    window->display();
}

#endif //RENDER_H
