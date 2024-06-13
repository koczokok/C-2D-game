//
// Created by pkury on 29/05/2024.
//

#include "Casual.h"
#include "fmt/core.h"

Casual::Casual(std::string textureName,
               sf::Vector2f texturePos,
               sf::Vector2f position,

               sf::Vector2f v,
               int shootTimer, bool isActive, int hearts,  EnemyType e, sf::Vector2f shootingSpeed) : Enemy
                                                                                                                              (textureName,
                                                                                                                               texturePos,
                                                                                                                               position,
                                                                                                                               v,
                                                                                                                               shootTimer,
                                                                                                                               isActive,
                                                                                                                               hearts,
                                                                                                                               e,
                                                                                                                               shootingSpeed), shootingSpeed(shootingSpeed) {


}


std::vector<Projectile*> Casual::shoot(const std::string &, sf::Vector2f playerPos) {

    return std::vector<Projectile*>{ new Projectile("",characterSprite.getPosition(), shootingSpeed)};

}

void Casual::collideEffect(Tile *tile, sf::Vector2f playerPos) {
    auto distanceToTileX = characterSprite.getPosition().x - tile->sprite.getPosition().x;
    auto distanceToTileY = characterSprite.getPosition().y - tile->sprite.getPosition().y;
    if(distanceToTileY < 20 and distanceToTileY < 40){
       velocity.y = -velocity.y;
    }
}