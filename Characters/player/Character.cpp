//
// Created by pkury on 19/05/2024.
//
#include "Character.h"
#include "../../Room/tile.h"
#include "../../Game/GameStates.h"
#include "fmt/core.h"
#include <algorithm>
#include "../../Game/game.h"

Character::Character(const std::string& textureName, sf::Vector2f texturePos, sf::Vector2f position, sf::Vector2f v,
                     int shootTimer, int hearts)
        : hearts(hearts), velocity(v), shootTimer(shootTimer) {
    if(!characterTexture.loadFromFile("./../resources/Enemy/" + textureName)) {
    }
    characterSprite.setTexture(characterTexture);
    characterSprite.setTextureRect(sf::IntRect(texturePos.x,texturePos.y,16,16));
    characterSprite.setPosition(position.x,position.y);
    projectiles = std::vector<Projectile *>();
}
bool Character::collide(Character* c) {
    auto playerBound = characterSprite.getGlobalBounds();
    auto nextPos = characterSprite.getGlobalBounds();
    auto cBounds = c->characterSprite.getGlobalBounds();
    nextPos.top += velocity.y;
    nextPos.left += velocity.x;
    if(cBounds.intersects(nextPos)){
        float overlapLeft = (playerBound.left + playerBound.width) - cBounds.left;
        float overlapRight = (cBounds.left + cBounds.width) - playerBound.left;
        float overlapTop = (playerBound.top + playerBound.height) - cBounds.top;
        float overlapBottom = (cBounds.top + cBounds.height) - playerBound.top;


        float minOverlapX = std::min(overlapLeft, overlapRight);
        float minOverlapY = std::min(overlapTop, overlapBottom);


        if (minOverlapX < minOverlapY) {

            if (overlapLeft < overlapRight) {
                velocity.x = 0.f;
                characterSprite.setPosition(cBounds.left - playerBound.width, playerBound.top);
            } else {
                velocity.x = 0.f;
                characterSprite.setPosition(cBounds.left + cBounds.width, playerBound.top);
            }
        } else {

            if (overlapTop < overlapBottom) {
                velocity.y = 0.f;

                characterSprite.setPosition(playerBound.left, cBounds.top - playerBound.height);
            } else {
                velocity.y = 0.f;

                characterSprite.setPosition(playerBound.left, cBounds.top + cBounds.height);
            }
        }
        return true;
    }
    return false;
}

bool Character::collide(Tile * tile) {
    auto playerBound = characterSprite.getGlobalBounds();
    auto nextPos = characterSprite.getGlobalBounds();
    auto tileBounds = tile->sprite.getGlobalBounds();
    nextPos.top += velocity.y;
    nextPos.left += velocity.x;
    if(tileBounds.intersects(nextPos) && !tile->isPassable){
//        isCollision = true;
        float overlapLeft = (playerBound.left + playerBound.width) - tileBounds.left;
        float overlapRight = (tileBounds.left + tileBounds.width) - playerBound.left;
        float overlapTop = (playerBound.top + playerBound.height) - tileBounds.top;
        float overlapBottom = (tileBounds.top + tileBounds.height) - playerBound.top;


        float minOverlapX = std::min(overlapLeft, overlapRight);
        float minOverlapY = std::min(overlapTop, overlapBottom);


        if (minOverlapX < minOverlapY) {

            if (overlapLeft < overlapRight) {
                velocity.x = 0.f;
                characterSprite.setPosition(tileBounds.left - playerBound.width, playerBound.top);
            } else {
                velocity.x = 0.f;
                characterSprite.setPosition(tileBounds.left + tileBounds.width, playerBound.top);
            }
        } else {

            if (overlapTop < overlapBottom) {
                velocity.y = 0.f;

                characterSprite.setPosition(playerBound.left, tileBounds.top - playerBound.height);
            } else {
                velocity.y = 0.f;

                characterSprite.setPosition(playerBound.left, tileBounds.top + tileBounds.height);
            }
        }
        return true;
    }

    return false;

}



sf::Vector2f Character::updateMovement(bool up, bool down, bool right, bool left) {
    if(right){
        velocity.x = 4;
    }
    if(left){
        velocity.x = -4;
    }
    if(up){
        velocity.y = -4;
    }
    if(down){
        velocity.y = 4;
    }
    if(!(right or left)){
        velocity.x = 0;
    }
    if(!(up or down)){
        velocity.y = 0;
    }
    characterSprite.setPosition(characterSprite.getPosition().x + velocity.x, characterSprite.getPosition().y + velocity.y);
    return {velocity.x, velocity.y};
}


void Character::checkProjectileCollisions(Tile *tile) {
    auto tileBound = tile->sprite.getGlobalBounds();

    for (auto p : projectiles) {
        if (tileBound.intersects(p ->circle.getGlobalBounds()) && !tile->isPassable) {
            auto iter = std::ranges::find(projectiles, p);
            projectiles.erase(iter);
        }
    }
}

void Character::moveAndDrawPlayerProjectiles(sf::RenderWindow& window) {
    for(auto i : projectiles){
        window.draw(i->circle);
        i->circle.move(i->velocity);
    }

}

void Character::checkIfPlayerAlive(Game& gameState) const {
        if(hearts <= 0){
            gameState.gameState = State::MENU;
        }
}


void Character::playerRender(sf::RenderWindow& window, Game& gameState ){
    window.draw(characterSprite);
    moveAndDrawPlayerProjectiles(window);
    checkIfPlayerAlive(gameState);
}

Character::~Character() {
        for(Projectile* p :projectiles){
            delete p;
        }
}


