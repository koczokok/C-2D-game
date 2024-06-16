//
// Created by pkury on 29/05/2024.
//

#ifndef PJC_GAME_ENEMY_H
#define PJC_GAME_ENEMY_H

#include "player/Character.h"
#include "eType.h"

class Enemy :  public Character {
public:
    Enemy(std::string, sf::Vector2f, sf::Vector2f, sf::Vector2f, int shootTimer, bool, int, EnemyType, sf::Vector2f, sf::Rect<float> hitbox);
    sf::Rect<float> hitbox;
    bool isActive;
    sf::Vector2f projectileSpeed;
    EnemyType enemyType;
    bool collide(Tile * tile);
    virtual void collideEffect(Tile *, sf::Vector2f);
    virtual void move(sf::Vector2f);
    virtual std::vector<Projectile*>shoot(const std::string &, sf::Vector2f);

};
#endif //PJC_GAME_ENEMY_H