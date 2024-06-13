//
// Created by pkury on 13/06/2024.
//
#include "mainMenu.h"
#include "fmt/core.h"
#include "chooseSave.h"

#include <filesystem>
#include "fmt/std.h"
MainMenu::MainMenu(sf::Font &font, sf::Vector2f size, sf::Vector2f initialPos, int margin, int numberOfButtons,
                   std::vector<std::string> buttonNames) :
        Menu(font, size, initialPos, margin, numberOfButtons,buttonNames) {
    isChoosingSave = false;


    sf::Texture* texture;
    if (!texture->loadFromFile("..//resources//s6.bmp")) {
    }
   saves = std::vector<sf::RectangleShape>();
    for(auto i = 0; i < 3;i++) {
        auto r = sf::RectangleShape(sf::Vector2f(300, 40));
        r.setPosition(50, 50 + 60 * i);
        r.setTexture(texture);
        saves.push_back(r);
    }
    auto filenames = std::vector<std::string>{};
    for(const auto& entry : std::filesystem::directory_iterator("./saves")){
        if(std::filesystem::is_regular_file(entry)){
            fmt::println("{}", entry.path().filename().string());
            filenames.push_back(entry.path().filename().string());
        }

    }
    isDialogOpen = false;

    createTexts(filenames, font);
}

void MainMenu::createTexts(const std::vector<std::string>& filenames, sf::Font &font){
    auto i = 0;
    for(auto k= 0;k < filenames.size(); k++){
        i++;
    savesTexts.push_back(createText(k, font, filenames[k]));
    }
    while (i <= 3){
        savesTexts.push_back(createText(i, font, "Empty"));
        i++;
    }
}

sf::Text MainMenu::createText(int i, sf::Font &font, std::string string){
    sf::Text text;
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);


    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(saves[i].getPosition().x + saves[i].getSize().x / 2.0f,
                     saves[i].getPosition().y + saves[i].getSize().y / 2.0f);
    return text;
}

void MainMenu::render(sf::RenderWindow & render) {
    if(isChoosingSave){
        for(auto v : saves){
            render.draw(v);
        }

        for(auto t : savesTexts){
            render.draw(t);
        }
//

    }else {
        for(auto b : buttons){
            render.draw(b);
        }
        for(auto t : buttonTexts){
            render.draw(t);
        }
    }


}



void MainMenu::checkButtonClick(sf::Vector2i vector, Game & game, World & world, sf::RenderWindow & renderWindow) {
    sf::Clock clock;
    if(game.gameState == State::MENU){
    if (isChoosingSave) {
                for(auto i = 0; i < saves.size(); i++){
                    if (saves[i].getGlobalBounds().contains(vector.x, vector.y)) {
                        if(savesTexts[i].getString() != "Empty"){
                            world = World(false, false);
                            game.loadSave("./saves/" + savesTexts[i].getString(), world);

                        }else {
                            fmt::println("Empty");
                        }
                    }
                }
        } else {
            for (auto i = 0; i < buttons.size(); i++) {
                if (buttons[i].getGlobalBounds().contains(vector.x, vector.y)) {
                    auto text = buttonTexts[i].getString();
                    if (text == "New Game") {
                        world = World();
                        fmt::println("Helo");
                        game.gameState = State::GAME;
                    }
                    if (text == "Load from save") {
                        fmt::println("Clicked");
                        isChoosingSave = true;

                        sf::sleep(sf::milliseconds(100));

                    }
                    if (text == "Exit")
                        game.gameState = State::QUIT;
                }
            }
        }
        }

    }

