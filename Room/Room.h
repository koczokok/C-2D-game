//
// Created by pkury on 29/05/2024.
//

#ifndef PJC_GAME_ROOM_H
#define PJC_GAME_ROOM_H
#include "tile.h"
#include "../Characters/Enemy.h"
#include "../Characters/Casual.h"

class Room {





public:
    bool isActive;
    std::vector<Tile*> exits;
    std::vector<Enemy*> enemies;
     Room(sf::Rect<float>, bool);
//    Room(const Room& other); // Copy constructor
//    Room& operator=(const Room& other); // Copy assignment operator
//    Room(Room&& other) noexcept; // Move constructor
//    Room& operator=(Room&& other) noexcept; // Move assignment operator
    ~Room(); // Destructor
    sf::Rect<float> bounds;
    std::vector<Tile*> spikes;
    void deactive();
//    void copy(const Room& other);
    void clearVectors();

};

#endif //PJC_GAME_ROOM_H