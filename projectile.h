//
// Created by pkury on 20/05/2024.
//
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <string>
#ifndef PJC_GAME_PROJECTILE_H
#define PJC_GAME_PROJECTILE_H

class Projectile {
public:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f velocity;
    sf::Vector2f position;
    sf::CircleShape circle;
    Projectile(std::string, sf::Vector2f, sf::Vector2f);
    void move();
};

#endif //PJC_GAME_PROJECTILE_H
