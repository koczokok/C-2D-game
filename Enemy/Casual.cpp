//
// Created by pkury on 29/05/2024.
//

#include "Casual.h"
#include "fmt/core.h"

Casual::Casual(std::string textureName,
               sf::Vector2f texturePos,
               sf::Vector2f position,
               sf::Vector2f size,
               sf::Vector2f v,
               float shootTimer, bool isActive) : Enemy
               (textureName, texturePos, position, size, v, shootTimer, isActive) {


}

void Casual::move() {
        characterSprite.move(velocity);
}

Projectile* Casual::shoot(const std::string&) {
    return new Projectile("",characterSprite.getPosition(), sf::Vector2f (-3,0));

}
