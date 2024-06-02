//
// Created by pkury on 18/05/2024.
//


#ifndef PJC_GAME_TILE_H
#define PJC_GAME_TILE_H
#include <SFML/Graphics.hpp>
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
    std::string textureName;
    Tile(sf::Vector2i, std::string, sf::Vector2f, bool, bool);
    bool createSprite(std::string);

};
#endif //PJC_GAME_TILE_H

