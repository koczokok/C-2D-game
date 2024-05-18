//
// Created by pkury on 18/05/2024.
//
#include <vector>
#include <SFML/Graphics.hpp>
#include "tile.h"
#ifndef PJC_GAME_WORLD_H
#define PJC_GAME_WORLD_H

class World {
    sf::Vector2i exitPos;
    sf::Vector2i playerPos;
    std::vector<sf::Vector2i> enemy;
    void setUpInitialState();
    void setEnemy();
    void setTiles();
    sf::Texture texture;
    bool setTexture();
public:
    std::vector<std::vector<Tile *>> tiles;
    World();
};

#endif //PJC_GAME_WORLD_H
