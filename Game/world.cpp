//
// Created by pkury on 18/05/2024.
//


#include <fstream>
#include <sstream>
#include "world.h"
#include "fmt/core.h"
#include "../Characters/Casual.h"
#include "../Characters/Speedy.h"
#include "../Characters/Fatman.h"
#include "../Characters/eType.h"
#include "../Characters/Boss.h"
#include "game.h"

World::World() {
    setUpInitialState(true);
    setUpEnemies(true);
    player = new Character("player.png", sf::Vector2f(0, 0), sf::Vector2f(200, 440),
                       sf::Vector2f(0, 0), 0.f, 5);
}

World::World(bool createRooms, bool createEnemies)  {

    setUpInitialState(createRooms);
    setUpEnemies(createEnemies);
    player = new Character("player.png", sf::Vector2f(0, 0), sf::Vector2f(200, 440),
                           sf::Vector2f(0, 0), 0.f, 5);
}

World::~World(){
    for(Room* r : rooms){
        for(Enemy* e : r->enemies){
            delete e;
        }
        for(Tile* s : r->spikes){
            delete s;
        }
        for(Tile* e : r->exits){
            delete e;
        }
        delete r;
    }
    delete player;
    for(const auto& t : tiles){
        for(Tile* t1: t){
            delete t1;
        }
    }
    for(Projectile* p : projectiles){
        delete p;
    }
}



void World::setUpInitialState(bool createRooms) {
    tiles.clear();
    std::vector<Tile *> tempMap;
    std::ifstream openFile("../resources/maps/map.txt");
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
        rooms.at(0)->enemies.push_back(new Casual(sf::Vector2f(0,0), sf::Vector2f(3*16, 4*16), sf::Vector2f(0.5,0.5), 100.f, false, 2, EnemyType::CASUAL, sf::Vector2f(3,0)));
        rooms.at(0)->enemies.push_back(new Fatman(sf::Vector2f(0,0), sf::Vector2f(16*21,5*11), sf::Vector2f(0,1), 140.f,
                                                  false, 5, EnemyType::FATMAN,sf::Vector2f (0,0)));
    rooms.at(4)->enemies.push_back(new Casual(sf::Vector2f(0,0), sf::Vector2f(16*52,30*16), sf::Vector2f(0,0.5), 150.f,
                                              false,2, EnemyType::CASUAL,sf::Vector2f (-3,0)));
    rooms.at(4)->enemies.push_back(new Casual(sf::Vector2f(0,0), sf::Vector2f(16*50,35*16), sf::Vector2f(0,0.5), 150.f,
                                              false,2, EnemyType::CASUAL,sf::Vector2f (-3,0)));
    rooms.at(1)->enemies.push_back(new Speedy(sf::Vector2f(0,0), sf::Vector2f(16*48,7*16), sf::Vector2f(0,3), 80.f,
                                              false, 3, EnemyType::SPEEDY,sf::Vector2f (0,0)));
    rooms.at(1)->enemies.push_back(new Casual(sf::Vector2f(0,0), sf::Vector2f(16*52,5*16), sf::Vector2f(0,0.5), 100.f,
                                              false,2, EnemyType::CASUAL,sf::Vector2f (-3,0)));
    rooms.at(1)->enemies.push_back(new Casual(sf::Vector2f(0,0), sf::Vector2f(16*37,12*16), sf::Vector2f(0,0.5), 100.f,
                                              false,2, EnemyType::CASUAL,sf::Vector2f (3,0)));
    rooms.at(1)->enemies.push_back(new Speedy(sf::Vector2f(0,0), sf::Vector2f(16*40,9*16), sf::Vector2f(0,3), 70.f,
                                              false, 3, EnemyType::SPEEDY,sf::Vector2f (0,0)));
    rooms.at(2)->enemies.push_back(new Fatman(sf::Vector2f(0,0), sf::Vector2f(16*83,5*16), sf::Vector2f(0,1), 170.f,
                                              false, 5, EnemyType::FATMAN,sf::Vector2f (0,0)));
    rooms.at(2)->enemies.push_back(new Speedy(sf::Vector2f(0,0), sf::Vector2f(16*67,9*16), sf::Vector2f(0,3), 70.f,
                                              false, 3, EnemyType::SPEEDY,sf::Vector2f (0,0)));
    rooms.at(2)->enemies.push_back(new Casual(sf::Vector2f(0,0), sf::Vector2f(16*71,12*16), sf::Vector2f(0,0.5), 100.f,
                                              false,2, EnemyType::CASUAL,sf::Vector2f (-3,0)));
    rooms.at(5)->enemies.push_back(new Casual( sf::Vector2f(0,0), sf::Vector2f(16*36, 61*16),sf::Vector2f(0,0.5), 70.f,false, 2,EnemyType::CASUAL ,sf::Vector2f (3,0)));
        rooms.at(5)->enemies.push_back(new Casual( sf::Vector2f(0,0), sf::Vector2f(16*52, 55*16),sf::Vector2f(0,0.5), 70.f,false, 2,EnemyType::CASUAL ,sf::Vector2f (-3,0)));
        rooms.at(5)->enemies.push_back(new Speedy(sf::Vector2f(0,0), sf::Vector2f(16*46,61*16), sf::Vector2f(0,2), 40.f,
                                                  false, 3, EnemyType::SPEEDY,sf::Vector2f (0,0)));
        rooms.at(6)->enemies.push_back(new Fatman(sf::Vector2f(0,0), sf::Vector2f(16*66,55*16), sf::Vector2f(0,1.5), 150.f,
                                                  false, 3, EnemyType::FATMAN,sf::Vector2f (0,0)));
        rooms.at(6)->enemies.push_back(new Speedy(sf::Vector2f(0,0), sf::Vector2f(16*84,61*16), sf::Vector2f(0,1.5), 90.f,
                                                  false, 3, EnemyType::SPEEDY,sf::Vector2f (0,0)));
        rooms.at(6)->enemies.push_back(new Speedy(sf::Vector2f(0,0), sf::Vector2f(16*84,55*16), sf::Vector2f(0,1.5), 105.f,
                                                  false, 3, EnemyType::SPEEDY,sf::Vector2f (0,0)));
        rooms.at(6)->enemies.push_back(new Fatman(sf::Vector2f(0,0), sf::Vector2f(16*66,61*16), sf::Vector2f(0,1.5), 120.f,
                                                  false, 3, EnemyType::FATMAN,sf::Vector2f (0,0)));
        rooms.at(7)->enemies.push_back(new Boss(sf::Vector2f(0,0), sf::Vector2f(16*106,58*16), sf::Vector2f(0,1.5), 120.f,
                                                  false, 3, EnemyType::SPEEDY,sf::Vector2f (0,0)));
        rooms.at(7)->enemies.push_back(new Boss(sf::Vector2f(0,0), sf::Vector2f(16*106,58*16), sf::Vector2f(0,1.5), 100.f,
                                                false, 3, EnemyType::BOSS,sf::Vector2f (0,0)));
        rooms.at(7)->enemies.push_back(new Fatman(sf::Vector2f(0,0), sf::Vector2f(16*114,54*16), sf::Vector2f(0,1.5), 160.f,
                                                false, 3, EnemyType::FATMAN,sf::Vector2f (0,0)));
        rooms.at(7)->enemies.push_back(new Fatman(sf::Vector2f(0,0), sf::Vector2f(16*114,61*16), sf::Vector2f(0,1.5), 140.f,
                                                false, 3, EnemyType::FATMAN,sf::Vector2f (0,0)));
    }
}

bool World::checkIfWon(Game& game){
    for(Room* r : rooms){
        if(not r->enemies.empty()){
            return false;
        }
    }
    game.gameState = State::WON;
    return true;
}

void World::checkEnemyCollisions(sf::Vector2f playerPos) {
    for(auto const& i : tiles ){
        for(auto const& t : i){
            chcekProjectileCollison(t);
            for(auto const& r: rooms){
                for(auto const & e : r->enemies){
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

void World::checkEnemyCollisionProjectile() {
    auto shouldbrake = false;
    for(auto& p : player->projectiles) {
        for (auto & r: rooms) {
            for (auto const &e: r->enemies) {
                sf::Rect<float> bounds = e->hitbox;
                bounds.left += e->characterSprite.getGlobalBounds().left;
                bounds.top += e->characterSprite.getGlobalBounds().top;
//                if (e->characterSprite.getGlobalBounds().intersects(p->circle.getGlobalBounds())) {
                if (bounds.intersects(p->circle.getGlobalBounds())) {
                    e->hearts--;
                    auto iterProjectile = std::ranges::find(player->projectiles, p);
                    player->projectiles.erase(iterProjectile);
                    if(e->hearts<=0) {
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

void World::checkPlayerHit() {
    for(auto & p : projectiles){
        if(p->circle.getGlobalBounds().intersects(player->characterSprite.getGlobalBounds())){
            projectiles.erase(std::ranges::find(projectiles, p));
            player->hearts--;

        }
    }

}

void World::drawTiles(sf::RenderWindow& window){
    for (auto const &tile: tiles) {
        for (auto const &j: tile) {
            window.draw(j->sprite);
            player->collide(j);
            player->checkProjectileCollisions(j);
        }
    }
}

void World::checkEnemyPlayerCollision(){
    for(auto r : rooms){
        for(auto e : r->enemies){
            player->collide(e);
        }
    }
}

void World::drawRoomAndEnemies(sf::RenderWindow & window) {
    for (auto &r: rooms) {

        if (!r->enemies.empty()) {
            for (auto &e: r->enemies) {
                if (r->isActive) {
                    for(auto & t : r->spikes){
                        window.draw(t->sprite);
                    }
                    window.draw(e->characterSprite);
                    e->move(player->characterSprite.getPosition());
                }
            }
        }
    }
}




void World::renderMain(sf::RenderWindow & window, int& shootTimer, Game& game) {
    checkEnemyCollisions(player->characterSprite.getPosition());
    checkPlayerHit();
    checkEnemyCollisionProjectile();
    drawTiles(window);
    activateRoom( shootTimer);
    checkEnemyPlayerCollision();
    drawEnemyProjectiles(window);
    drawRoomAndEnemies(window);
    checkIfWon(game);
}

void World::activateRoom (int& shootTimer) {
    for (auto &r: rooms) {
        if (r->bounds.intersects(player->characterSprite.getGlobalBounds()) && !r->enemies.empty()) {
            r->isActive = true;
            for (auto t: r->exits) {
                if (r->spikes.size() < r->exits.size()) {
                    r->spikes.push_back(
                            new Tile(sf::Vector2i(12, 2), "tileset.png", sf::Vector2f(t->pos.x, t->pos.y), false, false));
                }
                t->isPassable = false;
            }
        } else if (r->enemies.empty()) {
            r->spikes.clear();
            r->deactive();
        }

        if(shootTimer == INT32_MAX){
            shootTimer = 0;
        }
        if (r->isActive) {
                for (auto &e: r->enemies) {
                    if(shootTimer % e->shootTimer == 0){
                        for(auto p : e->shoot("", player->characterSprite.getPosition())){
                            projectiles.push_back(p);
                        }
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
