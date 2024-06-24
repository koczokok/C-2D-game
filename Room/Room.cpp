//
// Created by pkury on 29/05/2024.
//

#include "Room.h"
#include <iostream>
#include <sstream>
#include <string>

Room::Room(sf::Rect<float> bounds, bool isActive) : bounds(bounds), isActive(isActive) {


}

void Room::deactive() {
        isActive = false;
        for(auto& e : exits){
            e->isPassable = true;
        }
}
//
//Room::Room(const Room& other)
//        : isActive(other.isActive), bounds(other.bounds) {
//    copy(other);
//}
//
//Room& Room::operator=(const Room& other) {
//    if (this != &other) {
//        isActive = other.isActive;
//        bounds = other.bounds;
//        copy(other);
//    }
//    return *this;
//}
//
//Room::Room(Room&& other) noexcept
//        : isActive(other.isActive), bounds(other.bounds) {
//    exits = std::move(other.exits);
//    enemies = std::move(other.enemies);
//    spikes = std::move(other.spikes);
//    // Clear other's vectors
//    other.exits.clear();
//    other.enemies.clear();
//    other.spikes.clear();
//}
//
//Room& Room::operator=(Room&& other) noexcept {
//    if (this != &other) {
//        isActive = other.isActive;
//        bounds = other.bounds;
//        exits = std::move(other.exits);
//        enemies = std::move(other.enemies);
//        spikes = std::move(other.spikes);
//        // Clear other's vectors
//        other.exits.clear();
//        other.enemies.clear();
//        other.spikes.clear();
//    }
//    return *this;
//}
//
Room::~Room() {
    clearVectors();
}
//
//
//void Room::copy(const Room& other) {
//    // Copy exits
//    exits.clear();
//    exits.reserve(other.exits.size());
//    for (auto& exit : other.exits) {
//        exits.push_back(new Tile(*exit));
//    }
//
//    // Copy enemies
//    enemies.clear();
//    enemies.reserve(other.enemies.size());
//    for (auto& enemy : other.enemies) {
//        enemies.push_back(new Enemy(*enemy));
//    }
//
//    // Copy spikes
//    spikes.clear();
//    spikes.reserve(other.spikes.size());
//    for (auto& spike : other.spikes) {
//        spikes.push_back(new Tile(*spike));
//    }
//}
void Room::clearVectors() {
    for (auto& exit : exits) {
        delete exit;
    }
    exits.clear();

    for (auto& enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    for (auto& spike : spikes) {
        delete spike;
    }
    spikes.clear();
}