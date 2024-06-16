//
// Created by pkury on 29/05/2024.
//

#ifndef PJC_GAME_BOSS_H
#define PJC_GAME_BOSS_H
#include "Enemy.h"

class Boss : public Enemy {
public:
    Boss(sf::Vector2f, sf::Vector2f, sf::Vector2f, int, bool, int, EnemyType, sf::Vector2f);
    void move(sf::Vector2f) override;
    void collideEffect(Tile *, sf::Vector2f) override;
    std::vector<Projectile *> shoot(const std::string &, sf::Vector2f playerPos) override;
};
#endif //PJC_GAME_BOSS_H