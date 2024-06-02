//
// Created by pkury on 29/05/2024.
//

#include "Enemy.h"
#ifndef PJC_GAME_CASUAL_H
#define PJC_GAME_CASUAL_H
#pragma once


class Casual : public Enemy {
public:

    void collideEffect(Tile *, sf::Vector2f) override;
    std::vector<Projectile*>shoot(const std::string &, sf::Vector2f playerPos) override;
    Casual(std::string,sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f, float, bool, int);
};
#endif //PJC_GAME_CASUAL_H