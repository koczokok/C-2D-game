//
// Created by pkury on 18/05/2024.
//
#include "tile.h"
#include "fmt/core.h"


Tile::Tile(sf::Vector2i texturePos,const std::string& textureName, sf::Vector2f position, bool isPass, bool exit) :texturePos(texturePos), textureName(textureName), pos(position){

    scale = 1;

    sprite.setPosition(pos);
    isPassable = isPass;
    isExit = exit;
    left = sprite.getPosition().x;
    right = sprite.getPosition().x + (sprite.getLocalBounds().width * scale);
    top = sprite.getPosition().y;
    bottom = sprite.getPosition().y + (sprite.getLocalBounds().height * scale);
    createSprite(textureName);
}



bool Tile::createSprite(std::string textureName) {
    if(!texture.loadFromFile("./../resources/" + textureName)){
        return EXIT_FAILURE;
    }
    sprite.setTexture(texture);
    if(textureName == "tileset.png"){
        sprite.setTextureRect(sf::IntRect(texturePos.x *16,texturePos.y * 16,16,16));
    }
    return 0;
}

