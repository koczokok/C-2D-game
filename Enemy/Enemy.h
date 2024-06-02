//
// Created by pkury on 29/05/2024.
//
#include "../character.h"
#ifndef PJC_GAME_ENEMY_H
#define PJC_GAME_ENEMY_H



class Enemy : public Character {
public:
    Enemy(std::string,sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f, float, bool, int);
    bool isActive;
    bool collide(Tile * tile);
    virtual void collideEffect(Tile *, sf::Vector2f);
    virtual void move(sf::Vector2f);
    virtual std::vector<Projectile*>shoot(const std::string &, sf::Vector2f);
};
#endif //PJC_GAME_ENEMY_H