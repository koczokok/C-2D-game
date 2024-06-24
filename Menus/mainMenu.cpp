//
// Created by pkury on 13/06/2024.
//
#include "mainMenu.h"
#include "fmt/core.h"
#include "../Game/world.h"

#include <filesystem>
#include <utility>
#include "fmt/std.h"
MainMenu::MainMenu(sf::Font &font, sf::Vector2f size, sf::Vector2f initialPos, int margin, int numberOfButtons,
                   std::vector<std::string> buttonNames) :
        Menu(font, size, initialPos, margin, numberOfButtons, std::move(buttonNames)) {

}









void MainMenu::checkButtonClick(sf::Vector2i vector, Game &game, World &world) {
    if(game.gameState == State::MENU){
        getFilenamesAndCreateTexts();
    if (isChoosing) {
                for(auto i = 0; i < saves.size(); i++){
                    if (saves[i].getGlobalBounds().contains(vector.x, vector.y)) {
                        if(savesTexts[i].getString() != "Empty"){
                            world = World(false, false);
                            game.loadSave("./../resources/saves/" + savesTexts[i].getString(), world);
                            isChoosing = false;
                        }else {
                            world = World();
                            game.gameState = State::GAME;
                            isChoosing = false;
                        }
                    }
                }
        } else {
            for (auto i = 0; i < buttons.size(); i++) {
                if (buttons[i].getGlobalBounds().contains(vector.x, vector.y)) {
                    auto text = buttonTexts[i].getString();
                    if (text == "New Game") {
                        world = World();

                        game.gameState = State::GAME;
                    }
                    if (text == "Load from save") {

                        isChoosing = true;

                        sf::sleep(sf::milliseconds(100));

                    }
                    if (text == "Quit"){
                        fmt::println("{}","Exit");
                        game.gameState = State::QUIT;
                    }

                }
            }
        }
        }

    }

