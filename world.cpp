//
// Created by pkury on 18/05/2024.
//


#include <fstream>
#include <sstream>
#include "world.h"
#include "fmt/core.h"
#include "Enemy/Casual.h"

World::World() {
    setUpInitialState();
    setUpEnemies();
}



void World::setUpInitialState() {
    tiles.clear();
    std::vector<Tile *> tempMap;
    std::ifstream openFile("../maps/text.txt");
    auto cory = 0;
    auto corx = 0;
    auto test = 0;
    auto exits = std::vector<std::vector<Tile*>>(8, std::vector<Tile*>{});
    if(openFile.is_open()){
        while(!openFile.eof()){
            std::string str, value;
            std::getline(openFile, str);
            std::stringstream stream(str);

            while(std::getline(stream, value, '\t')) {

                    char x = value[0], y = value[2];
                    int p = value[4] - '0', e = value[6] - '0';

                    if (x == 'f'){
                        tempMap.push_back(
                                new Tile(sf::Vector2i(0,0), "RoomFloor.png",
                                         sf::Vector2f(corx * 16, cory * 16), !p,
                                         e));
                        rooms.push_back(new Room(sf::FloatRect(corx*16,cory*16, 336,160), false));
                    }

                    if ((!isdigit(x) || !isdigit(y))) {
                        corx++;
                    }
                    else {
                        tempMap.push_back(
                                new Tile(sf::Vector2i(x - '0', y - '0'), "tileset.png",
                                         sf::Vector2f(corx * 16, cory * 16), !p,
                                         e));
                        corx++;
                        test++;
                    }
                if(e > 0){
                    exits.at(e -1).push_back(tempMap.back());
                }

            }
                corx=0;
                tiles.push_back(tempMap);
                tempMap.clear();
                cory++;
            }
        }

    for(auto i=0; i < rooms.size(); i++){
      for(auto t : exits[i]){
          rooms[i]->exits.push_back(t);
      }
    }


}

void World::setUpEnemies() {
    rooms.at(4)->enemies.push_back(new Casual("dem.png",sf::Vector2f(0,18), sf::Vector2f(16*52,25*16), sf::Vector2f (16,16), sf::Vector2f(0,0.5), 40.f,
                                               false));
    rooms.at(4)->enemies.push_back(new Casual("dem.png",sf::Vector2f(0,18), sf::Vector2f(16*50,30*16), sf::Vector2f (16,16), sf::Vector2f(0,0.5), 40.f,
                                              false));


}

void World::checkEnemyCollisions() {
    for(auto const& i : tiles ){
        for(auto const& t : i){
            chcekProjectileCollison(t);
            for(auto const& r: rooms){
                for(auto const & e : r->enemies){
                    auto playerBound = e->characterSprite.getGlobalBounds();
                    auto nextPos = e->characterSprite.getGlobalBounds();
                    auto tileBounds = t->sprite.getGlobalBounds();
                    nextPos.top += e->velocity.y * 10;

                    auto distanceToTileX = e->characterSprite.getPosition().x - t->sprite.getPosition().x;
                    auto distanceToTileY = e->characterSprite.getPosition().y - t->sprite.getPosition().y;
                    nextPos.left += e->velocity.x * 10;
                    if(tileBounds.intersects(nextPos) && !t->isPassable){
                        if(distanceToTileY < 20 and distanceToTileY < 40){
                            e->velocity.y = - e->velocity.y;
                        }


                    }
                }
            }
        }
    }

}

void World::checkEnemyCollisionProjectile(Character& player) {
    auto shouldbrake = false;
    for(auto& p : player.projectiles) {
        for (auto & r: rooms) {
            for (auto const &e: r->enemies) {

                if (e->characterSprite.getGlobalBounds().intersects(p->circle.getGlobalBounds())) {
                    fmt::println("{}", "intersects");
                    auto iter = std::ranges::find(r->enemies.begin(), r->enemies.end(), e);
                    auto s = r->enemies.size();
                    fmt::println("{}", r->enemies.size());
                    r->enemies.erase(iter);
                    if(s == r->enemies.size()) {
                        fmt::println("{}", "something fucked");
                        fmt::println("{}", r->enemies.size());
                    }
                    fmt::println("{}", r->enemies.size());
                    auto iterProjectile = std::ranges::find(player.projectiles, p);
                    player.projectiles.erase(iterProjectile);
                    shouldbrake = true;
                    break;
                }
            }
            if(shouldbrake)
                break;
        }
        continue;
    }
}

void World::chcekProjectileCollison(Tile *tile) {
    for(auto& p : projectiles){
        if(p->circle.getGlobalBounds().intersects(tile->sprite.getGlobalBounds()) && !tile->isPassable){
            auto iter = std::ranges::find(projectiles, p);
            projectiles.erase(iter);
        }
    }

}

void World::checkPlayerHit(Character & player) {
    for(auto & p : projectiles){
        if(p->circle.getGlobalBounds().intersects(player.characterSprite.getGlobalBounds())){
            projectiles.erase(std::ranges::find(projectiles, p));
            player.hearts--;
        }
    }

}
