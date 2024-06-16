//
// Created by pkury on 02/06/2024.
//




#ifndef PJC_GAME_GAME_H
#define PJC_GAME_GAME_H
#include "GameStates.h"
#include "../Room/Room.h"

class Character;
class World;
class Game{
    static Room* createRoom(const std::string& data);

    static Enemy *createEnemy(const std::string& data);
    static Tile *createTile(const std::string& data);

    static Character* createPlayer(const std::string& data);
    std::string makeString(auto s);
public:
    Game();
    void save(World&, const std::string&);
    State gameState;
    void loadSave(const std::string& path, World& world);


};

#endif //PJC_GAME_GAME_H
