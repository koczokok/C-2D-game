//
// Created by pkury on 29/05/2024.
//

#ifndef PJC_GAME_FATMAN_H
#define PJC_GAME_FATMAN_H
#include "Enemy.h"


class Fatman : public Enemy {
public:
    Fatman(std::string,sf::Vector2f, sf::Vector2f,  sf::Vector2f, float, bool, int, EnemyType);
    void collideEffect(Tile *, sf::Vector2f) override;
    void move(sf::Vector2f) override;

    std::vector<Projectile*> shoot(const std::string &, sf::Vector2f playerPos) override;
};
#endif //PJC_GAME_FATMAN_H
