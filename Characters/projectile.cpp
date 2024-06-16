//
// Created by pkury on 20/05/2024.
//
#include "projectile.h"
#include "fmt/core.h"

Projectile::Projectile( sf::Vector2f pos, sf::Vector2f vel) {
    circle.setFillColor(sf::Color::Red);
    circle.setRadius(2.5);
    circle.setPosition(pos);
    velocity = vel;
}

void Projectile::move() {
    position = sf::Vector2f(position.x + velocity.x, position.y +velocity.y);
    circle.setPosition(position);
}

