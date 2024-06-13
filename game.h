//
// Created by pkury on 02/06/2024.
//




#ifndef PJC_GAME_GAME_H
#define PJC_GAME_GAME_H
#include "GameStates.h"
#include "Room/Room.h"

class Character;
class World;
class Game{
public:
    Game();
    void save(World&, std::string);
    State gameState;
    std::string makeString(auto s);

    void loadSave(std::string path, World& world);

    Room* createRoom(std::string data);

    Enemy *createEnemy(std::string data);

    World createNewGame();

    Tile *createTile(std::string data);

    static Character* createPlayer(std::string data);
};

#endif //PJC_GAME_GAME_H
