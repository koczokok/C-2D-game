//
// Created by pkury on 20/05/2024.
//
#include "projectile.h"
#include <fmt/core.h>

Projectile::Projectile(std::string textureName, sf::Vector2f pos, sf::Vector2f vel) {
//    if(!texture.loadFromFile("../" + textureName)){
//        fmt::println("{}", "I'm fuckeed");
//    }
//    sprite.setTexture(texture);
//    sprite.setTextureRect(sf::IntRect(0,0,16,16));
//    sprite.setPosition(pos);
    circle.setFillColor(sf::Color::Red);
    circle.setRadius(5.f);
    circle.setPosition(100,100);
    velocity = vel;
}

void Projectile::move() {
    position = sf::Vector2f(position.x + velocity.x, position.y +velocity.y);
    circle.setPosition(position);
}

