//
// Created by pkury on 29/05/2024.
//
#include "Enemy.h"
#ifndef PJC_GAME_BOSS_H
#define PJC_GAME_BOSS_H


class Boss : public Enemy {
public:
    Boss(std::string,sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f, float, bool, int);

};
#endif //PJC_GAME_BOSS_H