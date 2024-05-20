//
// Created by pkury on 19/05/2024.
//
#include "character.h"
#include "tile.h"
#include <fmt/core.h>

Character::Character(std::string textureName, sf::Vector2f position, sf::Vector2f size, sf::Vector2f v, float mS) {
    if(!characterTexture.loadFromFile("../" + textureName)){
        fmt::println("{}", "I'm fuckeed");
    }
    characterSprite.setTexture(characterTexture);
    characterSprite.setTextureRect(sf::IntRect(0,0,16,16));
    characterSprite.setPosition(position.x,position.y);
    projectiles = std::vector<Projectile *>();
    velocity = v;
}

void Character::updatePosition(float d, float a, float b, float c) {
    left = characterSprite.getPosition().x;
    right = characterSprite.getPosition().x + (characterSprite.getLocalBounds().width);
    up = characterSprite.getPosition().y;
    bottom = characterSprite.getPosition().y + (characterSprite.getLocalBounds().height);
}

void Character::collide(Tile * tile ) {
    auto playerBound = characterSprite.getGlobalBounds();
    auto nextPos = characterSprite.getGlobalBounds();
    auto tileBounds = tile->sprite.getGlobalBounds();
    nextPos.top += velocity.y;
    nextPos.left += velocity.x;
    if(tileBounds.intersects(nextPos) && !tile->isPassable){
        fmt::println("{}", "intersects");

        // Get the amount of overlap in each direction
        float overlapLeft = (playerBound.left + playerBound.width) - tileBounds.left;
        float overlapRight = (tileBounds.left + tileBounds.width) - playerBound.left;
        float overlapTop = (playerBound.top + playerBound.height) - tileBounds.top;
        float overlapBottom = (tileBounds.top + tileBounds.height) - playerBound.top;

        // Find the smallest overlap
        float minOverlapX = std::min(overlapLeft, overlapRight);
        float minOverlapY = std::min(overlapTop, overlapBottom);

        // Resolve collision based on the smallest overlap
        if (minOverlapX < minOverlapY) {
            // Resolve collision horizontally
            if (overlapLeft < overlapRight) {
                // Collision from the left
                velocity.x = 0.f;
                fmt::println("{}, Right {}, left: {}", "left", overlapRight, overlapLeft);
                characterSprite.setPosition(tileBounds.left - playerBound.width, playerBound.top);
            } else {
                // Collision from the right
                velocity.x = 0.f;
                fmt::println("{}", "right");
                characterSprite.setPosition(tileBounds.left + tileBounds.width, playerBound.top);
            }
        } else {
            // Resolve collision vertically
            if (overlapTop < overlapBottom) {
                // Collision from the top
                velocity.y = 0.f;
                fmt::println("{}", "top");
                characterSprite.setPosition(playerBound.left, tileBounds.top - playerBound.height);
            } else {
                // Collision from the bottom
                velocity.y = 0.f;
                fmt::println("{}", "bottom");
                characterSprite.setPosition(playerBound.left, tileBounds.top + tileBounds.height);
            }
        }
    }
}

void Character::shoot(){

}

void Character::updateMovement(bool up, bool down, bool right, bool left) {
    if(right){
        velocity.x = 5;
    }
    if(left){
        velocity.x = -5;
    }
    if(up){
        velocity.y = -5;
    }
    if(down){
        velocity.y = 5;
    }
    if(!(right or left)){
        velocity.x = 0;
    }
    if(!(up or down)){
        velocity.y = 0;
    }
}



