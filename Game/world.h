//
// Created by pkury on 18/05/2024.
//




#ifndef PJC_GAME_WORLD_H
#define PJC_GAME_WORLD_H
#include <vector>
#include "SFML/Graphics.hpp"
#include "../Room/tile.h"
#include "../Room/Room.h"
#include "GameStates.h"

class Game;
class World {

    void setUpEnemies(bool);
    void setUpInitialState(bool);
    void drawEnemyProjectiles(sf::RenderWindow&);
    void chcekProjectileCollison(Tile * tile);
    void checkEnemyCollisionProjectile();
    void checkPlayerHit();
    void drawTiles(sf::RenderWindow&);
    void drawRoomAndEnemies(sf::RenderWindow&);
    void activateRoom(int&);
    void checkEnemyCollisions(sf::Vector2f playerPos);
    bool checkIfWon(Game&);

public:
    Character* player;
    std::vector<std::vector<Tile *>> tiles;
    std::vector<Room *> rooms;
    std::vector<Projectile *> projectiles;

    World();
    World(bool, bool);
    void renderMain(sf::RenderWindow&, int&, Game&);


    void checkEnemyPlayerCollision();
};
#endif //PJC_GAME_WORLD_H