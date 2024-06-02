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
    gameState = State::MENU;
}


void Game::save(World & world, Character & character) {
    namespace sf = std::filesystem;
   std::ofstream outFile("example.txt");
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
                outFile << makeString(e->characterSprite.getTextureRect().getPosition().y);
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
        outFile << makeString(character.velocity.x) + "\t";
        outFile << makeString(character.velocity.y) + "\t";
        outFile << makeString(character.hearts) + "\t";
        outFile << makeString(character.shootTimer) + "\t";
        outFile << makeString(character.characterSprite.getPosition().x) + "\t";
        outFile << makeString(character.characterSprite.getPosition().y) + "\t";
        outFile << makeString(character.characterSprite.getTextureRect().getPosition().x) + "\t";
        outFile << makeString(character.characterSprite.getTextureRect().getPosition().y) + "\t";
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


void Game::loadSave(std::string path, World& world, Character& player){


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
//                        std::ranges::find(i,tile)
                        if(t->pos == tile->pos){
                            t->isPassable = false;
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
        int  hearts, eType;
        float vx, vy, px, py, tx,ty, shootTimer;

        ss  >> eType >> isActive >> shootTimer >> hearts >> vx >> vy >> px >> py >> tx >> ty;
        switch(eType){
            case CASUAL:
                return new Casual("dem.png", sf::Vector2f(tx,ty),sf::Vector2f (px,py),sf::Vector2f(vx,vy),shootTimer,isActive, hearts, EnemyType::CASUAL);
            case SPEEDY:
                return new Speedy("dem.png", sf::Vector2f(tx,ty),sf::Vector2f (px,py),sf::Vector2f(vx,vy),shootTimer,isActive, hearts, EnemyType::SPEEDY);
            case FATMAN:
                return new Fatman("dem.png", sf::Vector2f(tx,ty),sf::Vector2f (px,py),sf::Vector2f(vx,vy),shootTimer,isActive, hearts, EnemyType::FATMAN);
            case BOSS:
                return new Boss("dem.png", sf::Vector2f(tx,ty),sf::Vector2f (px,py),sf::Vector2f(vx,vy),shootTimer,isActive, hearts, EnemyType::BOSS);
            default:
                return new Enemy("dem.png", sf::Vector2f(tx,ty),sf::Vector2f (px,py),sf::Vector2f(vx,vy),shootTimer,isActive, hearts, EnemyType::BOSS);

        }

}

Character* Game::createPlayer(std::string data){
    std::stringstream ss(data);


    float vx,vy, shootTimer,px,py;
    int hearts, tx,ty;
    ss >> vx >> vy >>hearts >>shootTimer >>px >> py >> tx >> ty;
    return new Character("dem.png", sf::Vector2f(tx,ty), sf::Vector2f (px,py),sf::Vector2f(vx,vy),shootTimer,hearts);
}