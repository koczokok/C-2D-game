//
// Created by pkury on 18/05/2024.
//
#include <SFML/Graphics.hpp>
#ifndef PJC_GAME_TILE_H
#define PJC_GAME_TILE_H

class Tile {
public:
    bool isPassable;
    bool isExit;
    sf::Vector2<float> pos;
    sf::Vector2i texturePos;
    sf::Texture texture;
    sf::Sprite sprite;
    float top;
    float bottom;
    float left;
    float right;
    int scale;
    Tile(sf::Vector2i, const sf::Texture&, float, float, bool, bool);
    bool createSprite();

};

#endif //PJC_GAME_TILE_H
