//
// Created by pkury on 18/05/2024.
//
#include <vector>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "Room/Room.h"

#ifndef PJC_GAME_WORLD_H
#define PJC_GAME_WORLD_H

class World {
    sf::Vector2i exitPos;
    sf::Vector2i playerPos;
    std::vector<sf::Vector2i> enemy;
    void setUpEnemies();
    void setUpInitialState();
public:
    std::vector<std::vector<Tile *>> tiles;
    std::vector<Tile *> doors;
    std::vector<Room *> rooms;
    std::vector<Projectile *> projectiles;
    void checkEnemyCollisions();
    World();
    void chcekProjectileCollison(Tile * tile);
    void checkEnemyCollisionProjectile(Character&);
    void checkPlayerHit(Character&);
};

#endif //PJC_GAME_WORLD_H
