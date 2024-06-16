//
// Created by pkury on 29/05/2024.
//

#ifndef PJC_GAME_ROOM_H
#define PJC_GAME_ROOM_H
#include "tile.h"
#include "../Characters/enemy.h"
#include "../Characters/Casual.h"

class Room {





public:
    bool isActive;
    std::vector<Tile*> exits;
    std::vector<Enemy*> enemies;
     Room(sf::Rect<float>, bool);

    sf::Rect<float> bounds;
    std::vector<Tile*> spikes;
    void deactive();


};

#endif //PJC_GAME_ROOM_H