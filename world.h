//
// Created by pkury on 18/05/2024.
//


#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "Room/Room.h"
#include "GameStates.h"
#include "game.h"

#ifndef PJC_GAME_WORLD_H
#define PJC_GAME_WORLD_H

class World {


public:
    void setUpEnemies();
    void setUpInitialState();
    void drawEnemyProjectiles(sf::RenderWindow&);
    void chcekProjectileCollison(Tile * tile);
    void checkEnemyCollisionProjectile(Character&);
    void checkPlayerHit(Character&);
    void drawTiles(sf::RenderWindow&, Character&);
    void drawRoomAndEnemies(sf::RenderWindow&, Character&);
    void activateRoom(Character&, int&);
    std::vector<std::vector<Tile *>> tiles;
    std::vector<Room *> rooms;
    std::vector<Projectile *> projectiles;
    void checkEnemyCollisions(sf::Vector2f playerPos);
    World();
    void save( );
    void renderMain(sf::RenderWindow&, Character& player, int&);


};
#endif //PJC_GAME_WORLD_H