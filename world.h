//
// Created by pkury on 18/05/2024.
//




#ifndef PJC_GAME_WORLD_H
#define PJC_GAME_WORLD_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "Room/Room.h"
#include "GameStates.h"

class Game;
class World {


public:
    void setUpEnemies(bool);
    void setUpInitialState(bool);
    void drawEnemyProjectiles(sf::RenderWindow&);
    void chcekProjectileCollison(Tile * tile);
    void checkEnemyCollisionProjectile();
    void checkPlayerHit();
    void drawTiles(sf::RenderWindow&);
    void drawRoomAndEnemies(sf::RenderWindow&);
    void activateRoom(int&);
    std::vector<std::vector<Tile *>> tiles;
    std::vector<Room *> rooms;
    std::vector<Projectile *> projectiles;
    Character* player;
    void checkEnemyCollisions(sf::Vector2f playerPos);
    World();
    World(bool, bool);
    void save( );
    void renderMain(sf::RenderWindow&, int&);


};
#endif //PJC_GAME_WORLD_H