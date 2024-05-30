//
// Created by pkury on 29/05/2024.
//

#ifndef PJC_GAME_FATMAN_H
#define PJC_GAME_FATMAN_H

#include "enemy.h"

class Fatman : public Enemy {
public:
    Fatman(std::string,sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f, float, bool);
};

#endif //PJC_GAME_FATMAN_H
