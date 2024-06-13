//
// Created by pkury on 02/06/2024.
//
#include <filesystem>
#include <fstream>

#include "game.h"
#include "world.h"
#include "fmt/core.h"
#include "Enemy/Fatman.h"
#include "Enemy/Speedy.h"
#include "Enemy/Boss.h"

Game::Game() {
    // Final
    gameState = State::MENU;



//Test
//  gameState = State::GAME;
}


void Game::save(World & world, std::string filename) {
    namespace sf = std::filesystem;
//   std::ofstream outFile("./saves/" + filename);
    std::ofstream outFile("./saves/" + filename);
    if (outFile.is_open()) {
        for(auto r : world.rooms){
            outFile << "R \n";
            outFile << makeString(r->bounds.top) + "\t";
            outFile << makeString(r->bounds.height) + "\t" ;
            outFile << makeString(r->bounds.left) + "\t" ;
            outFile << makeString(r->bounds.width) + "\t" ;
            outFile << makeString(r->isActive);
            outFile << "\n";
            for(auto  e : r->enemies){

                outFile << "Enemy \n";
                outFile << makeString(e->enemyType)+ "\t";
                outFile << makeString(e->isActive) + "\t" ;
                outFile << makeString(e->shootTimer) + "\t" ;
                outFile << makeString(e->hearts)  + "\t";
                outFile << makeString(e->velocity.x) + "\t" ;
                outFile << makeString(e->velocity.y)  + "\t";
                outFile << makeString(e->characterSprite.getPosition().x) + "\t" ;
                outFile << makeString(e->characterSprite.getPosition().y) + "\t" ;
                outFile << makeString(e->characterSprite.getTextureRect().getPosition().x) + "\t";
                outFile << makeString(e->characterSprite.getTextureRect().getPosition().y) + "\t";
               outFile << makeString(e->projectileSpeed.x) + "\t";
               outFile << makeString(e->projectileSpeed.y);
                outFile << "\n";
            }
            for(auto e : r->exits){
                outFile << "Tile \n";
                outFile << makeString(e->texturePos.x)+ "\t";
                outFile << makeString(e->texturePos.y)+ "\t";
                outFile << makeString(e->pos.x)+ "\t";
                outFile << makeString(e->pos.y)+ "\t";
                outFile << makeString(e->isPassable)+ "\t";
                outFile << makeString(e->isExit)+ "\t";
                outFile << "\n";
            }
            for(auto s : r->spikes){
                outFile << "Spike \n";
                outFile << makeString(s->texturePos.x)+ "\t";
                outFile << makeString(s->texturePos.y)+ "\t";
                outFile << makeString(s->pos.x)+ "\t";
                outFile << makeString(s->pos.y)+ "\t";
                outFile << makeString(s->isPassable)+ "\t";
                outFile << makeString(s->isExit)+ "\t";
                outFile << "\n";
            }
        }
        outFile << "Player \n";
        outFile << makeString(world.player->velocity.x) + "\t";
        outFile << makeString(world.player->velocity.y) + "\t";
        outFile << makeString(world.player->hearts) + "\t";
        outFile << makeString(world.player->shootTimer) + "\t";
        outFile << makeString(world.player->characterSprite.getPosition().x) + "\t";
        outFile << makeString(world.player->characterSprite.getPosition().y) + "\t";
        outFile << makeString(world.player->characterSprite.getTextureRect().getPosition().x) + "\t";
        outFile << makeString(world.player->characterSprite.getTextureRect().getPosition().y) + "\t";
        // Write data to the file


        // Close the file
        outFile.close();
    }else {
      fmt::println("sheit");
    }


}

std::string Game::makeString(auto s){
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(3) << s;
        return oss.str();
}


void Game::loadSave(std::string path, World& world){


    std::ifstream inputFile(path);

    if(inputFile.is_open()){
        std::string line;
        while (std::getline(inputFile, line)) {
            if(line.starts_with("R")){
                std::getline(inputFile, line);
                world.rooms.push_back(createRoom(line));


            }
            if(line.starts_with("E")){
                std::getline(inputFile, line);
                world.rooms.back()->enemies.push_back(createEnemy(line));
            }
            if(line.starts_with("T")){

                std::getline(inputFile, line);
                Tile* tile = createTile(line);
                for(auto i : world.tiles){
                    for(auto t : i){
//
                        if(t->pos == tile->pos){
                            if(world.rooms.back()->isActive){
                                t->isPassable = false;
                            }
                            world.rooms.back()->exits.push_back(t);
                        }

                    }
                }

            }
            if(line.starts_with("S")){
                std::getline(inputFile, line);
                world.rooms.back()->spikes.push_back(createTile(line));
            }
            if(line.starts_with("P")){
                std::getline(inputFile, line);
                world.player = createPlayer(line);
            }

        }
        inputFile.close();
    }
        gameState = State::GAME;
}

Room* Game::createRoom(std::string data){
    std::stringstream ss(data);
    float top, height, left, width;
    bool isActive;
    ss >> top >> height >> left >> width >> isActive;

    return new Room(sf::Rect<float>(left, top, width, height), isActive);
}

Tile* Game::createTile(std::string data){
    std::stringstream ss(data);
    int  tx, ty;
    float px, py;
    bool isPass, isExit;

    ss >> tx >> ty >> px >> py >> isPass >> isExit;
    fmt::println("{},{},{}, {}",px,py, isPass, isExit);
    return new Tile(sf::Vector2i (tx,ty), "tileset.png", sf::Vector2f(px,py), isPass, isExit);

}

Enemy* Game::createEnemy(std::string data){
        std::stringstream ss(data);


        bool isActive;
        int  hearts, eType ,shootTimer;
        float vx, vy, px, py, tx,ty, psx, psy;


        ss  >> eType >> isActive >> shootTimer >> hearts >> vx >> vy >> px >> py >> tx >> ty >> psx >> psy;
        switch(eType){
            case CASUAL:
                return new Casual("dem.png", sf::Vector2f(tx,ty),sf::Vector2f (px,py),sf::Vector2f(vx,vy),shootTimer,isActive, hearts, EnemyType::CASUAL,sf::Vector2f(psx, psy) );
            case SPEEDY:
                return new Speedy("dem.png", sf::Vector2f(tx,ty),sf::Vector2f (px,py),sf::Vector2f(vx,vy),shootTimer,isActive, hearts, EnemyType::SPEEDY,sf::Vector2f(psx, psy));
            case FATMAN:
                return new Fatman("dem.png", sf::Vector2f(tx,ty),sf::Vector2f (px,py),sf::Vector2f(vx,vy),shootTimer,isActive, hearts, EnemyType::FATMAN,sf::Vector2f(psx, psy));
            case BOSS:
                return new Boss("dem.png", sf::Vector2f(tx,ty),sf::Vector2f (px,py),sf::Vector2f(vx,vy),shootTimer,isActive, hearts, EnemyType::BOSS,sf::Vector2f(psx, psy));
            default:
                return new Enemy("dem.png", sf::Vector2f(tx, ty), sf::Vector2f(px, py), sf::Vector2f(vx, vy),
                                 shootTimer, isActive, hearts, EnemyType::BOSS, sf::Vector2f(psx, psy));

        }

}

Character* Game::createPlayer(std::string data){
    std::stringstream ss(data);


    float vx,vy, shootTimer,px,py;
    int hearts, tx,ty;
    ss >> vx >> vy >>hearts >>shootTimer >>px >> py >> tx >> ty;
    return new Character("dem.png", sf::Vector2f(tx, ty), sf::Vector2f(px, py), sf::Vector2f(vx, vy), shootTimer, hearts);
}