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
    float shootTimer;
    sf::Sprite characterSprite;
    sf::Vector2f velocity;
    bool isCollision;
    std::vector<Projectile *> projectiles;
    float bottom, left, right, up;
    Character(const std::string&,sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f, float, int);
    virtual bool collide(Tile * tile);
    void checkProjectileCollisions(Tile * tile);
    bool checkDoors(std::vector<Tile*> tiles);
    sf::Vector2f updateMovement(bool, bool, bool, bool);
    int hearts;
    void movePlayerProjectiles();

};

#endif //PJC_GAME_CHARACTER_H
