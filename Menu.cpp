//
// Created by pkury on 01/06/2024.
//

#include "Menu.h"
#include "fmt/core.h"
#include "world.h"
#include "saveDialog.h"
#include "chooseSave.h"
#include <filesystem>

Menu::Menu(sf::Font& font ,sf::Vector2f size, sf::Vector2f initialPos, int margin, int numberOfButtons, std::vector<std::string> buttonNames) : texture(new sf::Texture()){

    dialog = SaveDialog();
    isDialog = false;
    isChoosing = false;
    setUpButtons(size, initialPos, margin, numberOfButtons);
    makeTexts(font, buttonNames);
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
    createTexts(filenames, font);


}

void Menu::setUpButtons(sf::Vector2f size, sf::Vector2f initialPos, int margin, int numberOfButtons) {
    if (!texture->loadFromFile("..//resources//s6.bmp")) {
        fmt::println("Fuckk");

    }
    for(auto i = 0; i < numberOfButtons; i++) {
        auto button = sf::RectangleShape(size);
        button.setTexture(texture);
        button.setPosition(initialPos.x, initialPos.y + i * (size.y + margin));
        buttons.push_back(button);
    }



}

void Menu::render(sf::RenderWindow & render) {
    if(isChoosing){
        for(auto v : saves){
            render.draw(v);
        }

        for(auto t : savesTexts){
            render.draw(t);
        }
    }else{
        for(auto b : buttons){
            render.draw(b);
        }
        for(auto t : buttonTexts){
            render.draw(t);
        }
    }



}

void Menu::makeTexts(sf::Font& font, std::vector<std::string> strings) {
    for(auto i = 0; i < buttons.size(); i++)
                {
        sf::Text text;
                    text.setFont(font); // Set the font
                    text.setString(strings[i]); // Set the string to display
                    text.setCharacterSize(20); // Set the character size
                    text.setFillColor(sf::Color::White); // Set the text color


                    sf::FloatRect textRect = text.getLocalBounds();
                    text.setOrigin(textRect.left + textRect.width / 2.0f,
                                   textRect.top + textRect.height / 2.0f);
                    text.setPosition(buttons[i].getPosition().x + buttons[i].getSize().x / 2.0f,
                                     buttons[i].getPosition().y + buttons[i].getSize().y / 2.0f);
                    buttonTexts.push_back(text);
                }
}





void Menu::checkButtonClick(sf::Vector2i vector, Game& game, World& world, sf::RenderWindow& renderWindow, sf::Font& font) {
    if(game.gameState == State::PAUSE){
        if(!isChoosing){
        for(auto i = 0; i < buttons.size(); i++){
            if(buttons[i].getGlobalBounds().contains(vector.x, vector.y)){
                auto text = buttonTexts[i].getString();

                    if(text == "Resume"){
                        fmt::println("Helo");
                        game.gameState = State::GAME;
                    }

                    if(text == "Save"){
                        isChoosing = true;

                    }

//                    if(text == "Exit")
//                        game.gameState = State::QUIT;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    isChoosing = false;
                }

            }
        }else {
            for(auto i = 0; i < saves.size(); i++){
                if(saves[i].getGlobalBounds().contains(vector.x, vector.y)){
                        if(not isDialog){
//                            fmt::println("{}", world.player->hearts);
                            auto v = SaveDialog::createDialog(game, world, savesTexts[i].getString());
                            isChoosing = false;
                            fmt::println("Crashed");
                            if(savesTexts[i].getString() == v){
                                fmt::println("Equak");
                            }else {

                                   std::string s ="./saves/" +savesTexts[i].getString();
                                if(remove(s.c_str()) == 0){
                                    fmt::println("Deleted");
                                }else {
                                    fmt::println("error");
                                }
                                savesTexts[i] = createText(i,font, v);
                            }
                            sf::sleep(sf::milliseconds(100));
                        }

                }
            }
        }

    }

}

void Menu::createTexts(const std::vector<std::string>& filenames, sf::Font &font){
    auto i = 0;
    for(auto k= 0;k < filenames.size(); k++){
        i++;
        savesTexts.push_back(createText(k, font, filenames[k]));
    }
    while (i < 3){
        fmt::println("Whillee");
        savesTexts.push_back(createText(i, font, "Empty"));
        i++;
    }
}

sf::Text Menu::createText(int i, sf::Font &font, std::string string){
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



