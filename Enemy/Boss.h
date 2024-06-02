//
// Created by pkury on 29/05/2024.
//

#ifndef PJC_GAME_BOSS_H
#define PJC_GAME_BOSS_H
#include "Enemy.h"

class Boss : public Enemy {
public:
    Boss(std::string,sf::Vector2f, sf::Vector2f, sf::Vector2f, float, bool, int, EnemyType);

};
#endif //PJC_GAME_BOSS_H