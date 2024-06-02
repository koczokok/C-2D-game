//
// Created by pkury on 19/05/2024.
//


#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "projectile.h"
#include "game.h"
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

    Character(const std::string&,sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f, float, int);
    virtual bool collide(Tile * tile);
    void checkProjectileCollisions(Tile * tile);

    sf::Vector2f updateMovement(bool, bool, bool, bool);
    int hearts;
    void moveAndDrawPlayerProjectiles(sf::RenderWindow& window);
    void checkIfPlayerAlive(Game&) const;

    void playerRender(sf::RenderWindow&, Game&);
};
#endif //PJC_GAME_CHARACTER_H
