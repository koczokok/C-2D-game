//
// Created by pkury on 29/05/2024.
//

#ifndef PJC_GAME_CASUAL_H
#define PJC_GAME_CASUAL_H

#include "enemy.h"

class Casual : public Enemy {
public:
    void move();
    Projectile* shoot(const std::string&);
    Casual(std::string,sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f, float, bool);
};
#endif //PJC_GAME_CASUAL_H
