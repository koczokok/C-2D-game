//
// Created by pkury on 19/05/2024.
//
#include <string>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "projectile.h"
#ifndef PJC_GAME_CHARACTER_H
#define PJC_GAME_CHARACTER_H

class Character{
public:
    sf::Texture characterTexture;
    sf::Sprite characterSprite;
    sf::Vector2f velocity;
    float shootTimer;
    std::vector<Projectile *> projectiles;
    float bottom, left, right, up;
    Character(std::string,sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f, float);
    void collide(Tile * tile);
    void checkProjectileCollisions(Tile * tile);
    void updateMovement(bool, bool, bool, bool);

};

#endif //PJC_GAME_CHARACTER_H
