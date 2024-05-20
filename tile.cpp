//
// Created by pkury on 18/05/2024.
//
#include "tile.h"
#include "fmt/core.h"


Tile::Tile(sf::Vector2i tPosition,const  sf::Texture& t, sf::Vector2f p, bool isPass, bool exit){
    texturePos = tPosition;
    texture = t;
    scale = 1;
    pos = p;
    sprite.setPosition(pos);
    isPassable = isPass;
    isExit = exit;
    left = sprite.getPosition().x;
    right = sprite.getPosition().x + (sprite.getLocalBounds().width * scale);
    top = sprite.getPosition().y;
    bottom = sprite.getPosition().y + (sprite.getLocalBounds().height * scale);
    createSprite();
}



bool Tile::createSprite() {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(texturePos.x *16,texturePos.y * 16,16,16));
    fmt::println("{}, {}", "Worked2", isPassable);
    return 0;
}

