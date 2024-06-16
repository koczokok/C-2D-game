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