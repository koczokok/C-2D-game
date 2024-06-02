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
//Room::Room(std::string data) : Room(sf::Rect<float>(left, top, width, height), isActive){
//    std::stringstream ss(data);
//    float top, height, left, width;
//    bool isActive;
//    ss >> top >> height >> left >> width >> isActive;
//    Room(sf::Rect<float>(left, top, width, height), isActive);
//
//}
//void Room::prepareData(std::string data){
//    std::stringstream ss(data);
//    float top, height, left, width;
//    bool isActive;
//    ss >> top >> height >> left >> width >> isActive;
//    Room(sf::Rect<float>(left, top, width, height), isActive);
//}
