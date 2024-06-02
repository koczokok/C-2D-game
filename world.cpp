//
// Created by pkury on 18/05/2024.
//


#include <fstream>
#include <sstream>
#include "world.h"
#include "fmt/core.h"
#include "Enemy/Casual.h"
#include "Enemy/Speedy.h"
#include "Enemy/Fatman.h"
#include "eType.h"

World::World() {
    setUpInitialState(true);
    setUpEnemies(true);
    player = new Character("dem.png", sf::Vector2f(0, 0), sf::Vector2f(200, 440),
              sf::Vector2f(0, 0), 20.f, 5);
    fmt::println("{}", "Random world created");
}

World::World(bool createRooms, bool createEnemies) {
    setUpInitialState(createRooms);
    setUpEnemies(createEnemies);
}



void World::setUpInitialState(bool createRooms) {
    tiles.clear();
    std::vector<Tile *> tempMap;
    std::ifstream openFile("../maps/text.txt");
    auto cory = 0;
    auto corx = 0;
    auto test = 0;
    auto exits = std::vector<std::vector<Tile *>>(8, std::vector<Tile *>{});
    if (openFile.is_open()) {
        while (!openFile.eof()) {
            std::string str, value;
            std::getline(openFile, str);
            std::stringstream stream(str);

            while (std::getline(stream, value, '\t')) {

                char x = value[0], y = value[2];
                int p = value[4] - '0', e = value[6] - '0';

                if (x == 'f') {
                    tempMap.push_back(
                            new Tile(sf::Vector2i(0, 0), "RoomFloor.png",
                                     sf::Vector2f(corx * 16, cory * 16), !p,
                                     e));
                    if (createRooms) {
                        rooms.push_back(new Room(sf::FloatRect(corx * 16, cory * 16, 336, 160), false));
                    }
                }
                if (x == 'c') {
                    tempMap.push_back(
                            new Tile(sf::Vector2i(0, 0), "corridor.png",
                                     sf::Vector2f(corx * 16, cory * 16), !p,
                                     e));
                }
                if (x == 'v')
                    tempMap.push_back(
                            new Tile(sf::Vector2i(0, 0), "Vcorridor.png",
                                     sf::Vector2f(corx * 16, cory * 16), !p,
                                     e));

                if ((!isdigit(x) || !isdigit(y))) {
                    corx++;
                } else {
                    tempMap.push_back(
                            new Tile(sf::Vector2i(x - '0', y - '0'), "tileset.png",
                                     sf::Vector2f(corx * 16, cory * 16), !p,
                                     e));
                    corx++;
                    test++;
                }

                if (e > 0 and createRooms) {
                    exits.at(e - 1).push_back(tempMap.back());
                }

            }
            corx = 0;

            tiles.push_back(tempMap);
            tempMap.clear();
            cory++;
        }
    }
    if (createRooms) {
        for (auto i = 0; i < rooms.size(); i++) {
            for (auto t: exits[i]) {
                rooms[i]->exits.push_back(t);
            }
        }
    }
}




void World::setUpEnemies(bool is) {
    if(is){
    rooms.at(4)->enemies.push_back(new Casual("dem.png",sf::Vector2f(0,16), sf::Vector2f(16*52,30*16), sf::Vector2f(0,0.5), 40.f,
                                              false,2, EnemyType::CASUAL));
    rooms.at(4)->enemies.push_back(new Casual("dem.png",sf::Vector2f(0,16), sf::Vector2f(16*50,35*16), sf::Vector2f(0,0.5), 40.f,
                                              false,2, EnemyType::SPEEDY));
//    rooms.at(1)->enemies.push_back(new Speedy("dem.png",sf::Vector2f(16,0), sf::Vector2f(16*48,7*16), sf::Vector2f(0,3), 40.f,
//                                              false, 3));
//    rooms.at(1)->enemies.push_back(new Casual("dem.png",sf::Vector2f(0,16), sf::Vector2f(16*52,5*16), sf::Vector2f(0,0.5), 40.f,
//                                              false,2));
//    rooms.at(1)->enemies.push_back(new Casual("dem.png",sf::Vector2f(0,16), sf::Vector2f(16*37,12*16), sf::Vector2f(0,0.5), 40.f,
//                                              false,2));
//    rooms.at(1)->enemies.push_back(new Speedy("dem.png",sf::Vector2f(16,0), sf::Vector2f(16*40,9*16), sf::Vector2f(0,3), 40.f,
//                                              false, 3));
//    rooms.at(2)->enemies.push_back(new Fatman("dem.png",sf::Vector2f(64,0), sf::Vector2f(16*85,5*16), sf::Vector2f(0,3), 40.f,
//                                              false, 5));
//    rooms.at(2)->enemies.push_back(new Speedy("dem.png",sf::Vector2f(16,0), sf::Vector2f(16*67,9*16), sf::Vector2f(0,3), 40.f,
//                                              false, 3));
//    rooms.at(2)->enemies.push_back(new Casual("dem.png",sf::Vector2f(0,16), sf::Vector2f(16*71,12*16), sf::Vector2f(0,0.5), 40.f,
//                                              false,2));
    }
}

void World::checkEnemyCollisions(sf::Vector2f playerPos) {
    for(auto const& i : tiles ){
        for(auto const& t : i){
            chcekProjectileCollison(t);
            for(auto const& r: rooms){
                for(auto const & e : r->enemies){
                    auto playerBound = e->characterSprite.getGlobalBounds();
                    auto nextPos = e->characterSprite.getGlobalBounds();
                    auto tileBounds = t->sprite.getGlobalBounds();
                    nextPos.top += e->velocity.y * 10;
                    nextPos.left += e->velocity.x * 10;
                    if(tileBounds.intersects(nextPos) && !t->isPassable){
                        e->collideEffect(t, playerPos);


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
                    e->hearts--;
                    auto iterProjectile = std::ranges::find(player.projectiles, p);
                    player.projectiles.erase(iterProjectile);
                    if(e->hearts<=0) {
                        fmt::println("{}", "intersects");
                        auto iter = std::ranges::find(r->enemies.begin(), r->enemies.end(), e);
                        r->enemies.erase(iter);
                        shouldbrake = true;
                        break;
                    }
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

void World::drawTiles(sf::RenderWindow& window, Character& player){
    for (auto const &tile: tiles) {
        for (auto const &j: tile) {
            window.draw(j->sprite);
            player.collide(j);
            player.checkProjectileCollisions(j);
        }
    }
}

void World::drawRoomAndEnemies(sf::RenderWindow & window, Character & player) {
    for (auto &r: rooms) {

        if (r->enemies.size() > 0) {
            for (auto &e: r->enemies) {
                if (r->isActive) {
                    for(auto & t : r->spikes){
                        window.draw(t->sprite);
                    }
                    window.draw(e->characterSprite);
                    e->move(player.characterSprite.getPosition());
                }
            }
        }
    }
}

void World::renderMain(sf::RenderWindow & window, Character & player, int& shootTimer) {
    checkEnemyCollisions(player.characterSprite.getPosition());
    checkPlayerHit(player);
    checkEnemyCollisionProjectile(player);

    drawTiles(window, player);
    activateRoom(player, shootTimer);
    drawEnemyProjectiles(window);
    drawRoomAndEnemies(window, player);
}

void World::activateRoom(Character & player, int& shootTimer) {
    for (auto &r: rooms) {
        if (r->bounds.intersects(player.characterSprite.getGlobalBounds()) && !r->enemies.empty()) {
            r->isActive = true;
            for (auto t: r->exits) {
                if (r->spikes.size() < r->exits.size()) {
                    r->spikes.push_back(
                            new Tile(sf::Vector2i(12, 2), "tileset.png", sf::Vector2f(t->pos.x, t->pos.y), 0, 0));
                }
                t->isPassable = false;
            }
        } else if (r->enemies.empty()) {
            r->spikes.clear();
            r->deactive();
        }
        if (shootTimer > 40) {
            if (r->isActive) {
                for (auto &e: r->enemies) {
                    for(auto p : e->shoot("", player.characterSprite.getPosition())){
                        projectiles.push_back(p);
                    }
                    shootTimer = 0;
                }
            }
        }
    }
}

void World::drawEnemyProjectiles(sf::RenderWindow & window) {
    for (auto const &p: projectiles) {
        window.draw(p->circle);
        p->circle.move(p->velocity);
    }

}
