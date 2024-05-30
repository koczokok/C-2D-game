//
// Created by pkury on 29/05/2024.
//

#include "enemy.h"
#include "fmt/core.h"


Enemy::Enemy(std::string textureName, sf::Vector2f texturePos, sf::Vector2f position, sf::Vector2f size, sf::Vector2f v, float shootTimer, bool isActive) : Character(

        textureName, texturePos, position, size, v, shootTimer, 1), isActive(isActive){

}

bool Enemy::collide(Tile *tile) {
    auto playerBound = characterSprite.getGlobalBounds();
    auto nextPos = characterSprite.getGlobalBounds();
    auto tileBounds = tile->sprite.getGlobalBounds();
    nextPos.top += velocity.y * 10;

    auto distanceToTileX = characterSprite.getPosition().x - tile->sprite.getPosition().x;
    auto distanceToTileY = characterSprite.getPosition().y - tile->sprite.getPosition().y;
    nextPos.left += velocity.x * 10;
    if(tileBounds.intersects(nextPos) && !tile->isPassable){
        if(distanceToTileY < 20 and distanceToTileY < 40){
            velocity.y = - velocity.y;
        }


    }

    return false;
}
