//
// Created by pkury on 19/05/2024.
//
#include <string>
#include <SFML/Graphics.hpp>
#include "tile.h"

#ifndef PJC_GAME_CHARACTER_H
#define PJC_GAME_CHARACTER_H

class Character{
public:
    Character(std::string, sf::Vector2f, sf::Vector2f, sf::Vector2f, float);
    sf::Texture characterTexture;
    sf::Sprite characterSprite;
    sf::Vector2f velocity;
    bool isCollide;
    float movementSpeed;
    float bottom, left, right, up;
    void updatePosition(float, float, float, float);
    void collide(Tile * tile);
    void updateMovement(bool, bool, bool, bool);

};

#endif //PJC_GAME_CHARACTER_H
