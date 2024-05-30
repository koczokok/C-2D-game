//
// Created by pkury on 29/05/2024.
//

#ifndef PJC_GAME_ENEMY_H
#define PJC_GAME_ENEMY_H

#include "../character.h"

class Enemy : public Character {
public:
    Enemy(std::string,sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f, float, bool);
    bool isActive;
    bool collide(Tile * tile);
};
#endif //PJC_GAME_ENEMY_H
