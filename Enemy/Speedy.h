//
// Created by pkury on 29/05/2024.
//

#ifndef PJC_GAME_SPEEDY_H
#define PJC_GAME_SPEEDY_H
#include "enemy.h"

class Speedy : public Enemy {
public:
    Speedy(std::string,sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f, float, bool);
};

#endif //PJC_GAME_SPEEDY_H
