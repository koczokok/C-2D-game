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
               float shootTimer, bool isActive, int hearts) : Enemy
               (textureName, texturePos, position, size, v, shootTimer, isActive, hearts) {


}


std::vector<Projectile*> Casual::shoot(const std::string &, sf::Vector2f playerPos) {

    return std::vector<Projectile*>{ new Projectile("",characterSprite.getPosition(), sf::Vector2f (-3,0))};

}

void Casual::collideEffect(Tile *tile, sf::Vector2f playerPos) {
    auto distanceToTileX = characterSprite.getPosition().x - tile->sprite.getPosition().x;
    auto distanceToTileY = characterSprite.getPosition().y - tile->sprite.getPosition().y;
    if(distanceToTileY < 20 and distanceToTileY < 40){
       velocity.y = -velocity.y;
    }
}