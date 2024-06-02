//
// Created by pkury on 29/05/2024.
//

#include "Speedy.h"
#include "fmt/core.h"

Speedy::Speedy(std::string textureName,
               sf::Vector2f texturePos,
               sf::Vector2f position,

               sf::Vector2f v,
               float shootTimer, bool isActive, int hearts, EnemyType e) : Enemy
                                           (textureName, texturePos, position, v, shootTimer, isActive, hearts, e) {


}

std::vector<Projectile*> Speedy::shoot(const std::string &, sf::Vector2f playerPos) {
    auto distanceToPlayerY = characterSprite.getPosition().y - playerPos.y;
    auto distanceToPlayerX = characterSprite.getPosition().x - playerPos.x;
    auto sum = std::abs(distanceToPlayerY) + std::abs(distanceToPlayerX);
    auto sy = distanceToPlayerY / sum;
    auto sx = distanceToPlayerX / sum;
//    fmt::println("{}, {}", sy, sx);
    return std::vector<Projectile*>{ new Projectile("",characterSprite.getPosition(), sf::Vector2f (-sx * 2.5,-sy * 2.5))};

}



void Speedy::collideEffect(Tile *tile, sf::Vector2f playerPos) {
    auto distanceToTileX = characterSprite.getPosition().x - tile->sprite.getPosition().x;
    auto distanceToTileY = characterSprite.getPosition().y - tile->sprite.getPosition().y;
    if (distanceToTileY < 20 and distanceToTileY < 40) {
        velocity.y = -velocity.y;
    }
    if (distanceToTileX < 20 and distanceToTileX < 40) {
        velocity.x = -velocity.x;
    }

}

void Speedy::move(sf::Vector2f playerPos) {
    auto distanceToPlayerY = characterSprite.getPosition().y - playerPos.y;
    auto distanceToPlayerX = characterSprite.getPosition().x - playerPos.x;
    if (0 > distanceToPlayerY) {
        velocity.y = 0.5;
    } else if (distanceToPlayerY == 0) {
        velocity.y = 0;
    }else {
        velocity.y = -0.5;
    }
    if (0 > distanceToPlayerX) {
        velocity.x = 0.5;
    } else if (distanceToPlayerY == 0) {
        velocity.x = 0;
    }else {
        velocity.x = -0.5;
    }
    characterSprite.move(velocity);
}
