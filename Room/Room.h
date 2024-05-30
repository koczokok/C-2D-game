//
// Created by pkury on 29/05/2024.
//

#ifndef PJC_GAME_ROOM_H
#define PJC_GAME_ROOM_H

#include "../tile.h"
#include "../Enemy/enemy.h"
#include "../Enemy/Casual.h"

class Room {





public:
    bool isActive;
    std::vector<Tile*> exits;
    std::vector<Casual*> enemies;
     Room(sf::Rect<float>, bool);
    sf::Rect<float> bounds;
    void deactive();
};

#endif //PJC_GAME_ROOM_H
