//
// Created by pkury on 18/05/2024.
//


#include <fstream>
#include <sstream>
#include "world.h"
#include "fmt/core.h"

World::World() {
    setUpInitialState();
}



void World::setUpInitialState() {
    tiles.clear();
    if(!texture.loadFromFile("C:\\Users\\pkury\\CLionProjects\\PJC-Game\\tileset.png")){
        fmt::println("{}", "I'm fucked");
    }
    std::vector<Tile *> tempMap;
    std::ifstream openFile("../map.txt");
    auto c = 0;
    if(openFile.is_open()){
        while(!openFile.eof()){
            std::string str, value;
            std::getline(openFile, str);
            std::stringstream stream(str);

            while(std::getline(stream, value, ' ')) {
                if(!value.empty()) {
                    char x = value[0], y = value[2];
                    int p = value[4] - '0', e = value[6] - '0';
                    fmt::println("P: {}", p);

                    if (!isdigit(x) || !isdigit(y))
                        tempMap.push_back(
                                new Tile(sf::Vector2i(-1, -1), texture, sf::Vector2f(tempMap.size() * 16,c * 16), !p, e));
                    else
                        tempMap.push_back(
                                new Tile(sf::Vector2i(x - '0', y - '0'), texture,sf::Vector2f(tempMap.size() * 16, c * 16), !p,
                                         e));
                }
            }

                tiles.push_back(tempMap);
                tempMap.clear();
                c++;
            }
        }


}