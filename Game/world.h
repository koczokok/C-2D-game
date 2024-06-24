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
    void copyTiles(const World& other);
    void copyRooms(const World& other);
    void copyProjectiles(const World& other);
    void cleanup();
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
    World(const World& other); // Copy constructor
    World(World&& other) noexcept; // Move constructor
    World(bool param1, bool param2);
    ~World(); // Destructor
    void renderMain(sf::RenderWindow& window, int& someInt, Game& game);
    void checkEnemyPlayerCollision();

    World& operator=(const World& other); // Copy assignment operator
    World& operator=(World&& other) noexcept;
};
#endif //PJC_GAME_WORLD_H