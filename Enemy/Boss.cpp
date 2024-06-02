//
// Created by pkury on 29/05/2024.
//

#include "Boss.h"

Boss::Boss(std::string textureName,
           sf::Vector2f texturePos,
           sf::Vector2f position,

           sf::Vector2f v,
           float shootTimer, bool isActive, int hearts, EnemyType e) : Enemy
                                                      (textureName, texturePos, position, v, shootTimer,
                                                       isActive, hearts, e) {


}