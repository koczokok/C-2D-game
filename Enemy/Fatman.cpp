//
// Created by pkury on 29/05/2024.
//

#include "Fatman.h"
#include "fmt/core.h"
#include <cmath>

Fatman::Fatman(std::string textureName,
               sf::Vector2f texturePos,
               sf::Vector2f position,
               sf::Vector2f size,
               sf::Vector2f v,
               float shootTimer, bool isActive, int hearts) : Enemy
                                           (textureName, texturePos, position, size, v, shootTimer, isActive, hearts) {


}

std::vector<Projectile*> Fatman::shoot(const std::string &, sf::Vector2f playerPos) {
    auto proj = std::vector<Projectile*>{};
    auto direction = std::vector<sf::Vector2f>{sf::Vector2f(-3,0), sf::Vector2f(3,0), sf::Vector2f(0,3), sf::Vector2f(0,-3),
                                               sf::Vector2f (sqrt(4.5), sqrt(4.5)),sf::Vector2f (-sqrt(4.5), -sqrt(4.5)),sf::Vector2f (-sqrt(4.5), sqrt(4.5)), sf::Vector2f (sqrt(4.5), -sqrt(4.5))};
    for(auto i = 0; i < direction.size(); i++){
        proj.push_back(new Projectile("",characterSprite.getPosition(), direction[i]));
    }


    return proj;

}



void Fatman::collideEffect(Tile *tile, sf::Vector2f playerPos) {
    auto distanceToTileX = characterSprite.getPosition().x - tile->sprite.getPosition().x;
    auto distanceToTileY = characterSprite.getPosition().y - tile->sprite.getPosition().y;
    if (distanceToTileY < 20 and distanceToTileY < 40) {
        velocity.y = -velocity.y;
    }
    if (distanceToTileX < 20 and distanceToTileX < 40) {
        velocity.x = -velocity.x;
    }

}

void Fatman::move(sf::Vector2f playerPos) {
    auto distanceToPlayerY = characterSprite.getPosition().y - playerPos.y;
    auto distanceToPlayerX = characterSprite.getPosition().x - playerPos.x;
    if (0 > distanceToPlayerY) {
        velocity.y = 0.1;
    } else if (distanceToPlayerY == 0) {
        velocity.y = 0;
    }else {
        velocity.y = -0.1;
    }
    if (0 > distanceToPlayerX) {
        velocity.x = 0.1;
    } else if (distanceToPlayerY == 0) {
        velocity.x = 0;
    }else {
        velocity.x = -0.1;
    }
    characterSprite.move(velocity);
}
