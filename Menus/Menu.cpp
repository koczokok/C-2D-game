//
// Created by pkury on 01/06/2024.
//

#include "Menu.h"
#include "fmt/core.h"
#include "../Game/world.h"


#include <filesystem>
#include <iostream>
#include <utility>

Menu::Menu(sf::Font &font, sf::Vector2f size, sf::Vector2f initialPos, int margin, int numberOfButtons,
           std::vector<std::string> buttonNames) : texture(new sf::Texture()), font(font) {


    isDialog = false;
    isChoosing = false;
    setUpButtons(size, initialPos, margin, numberOfButtons);
    makeTexts(font, std::move(buttonNames));
    saves = std::vector<sf::RectangleShape>();
    for(auto i = 0; i < 3;i++) {
        auto r = sf::RectangleShape(sf::Vector2f(300, 40));
        r.setPosition(50, 50 + 60 * i);
        r.setTexture(texture);
        saves.push_back(r);
    }

    getFilenamesAndCreateTexts();

}

void Menu::getFilenamesAndCreateTexts(){
    auto filenames = std::vector<std::string>{};
    for(const auto& entry : std::filesystem::directory_iterator("./../resources/saves")){
        if(std::filesystem::is_regular_file(entry)){
            filenames.push_back(entry.path().filename().string());
        }

    }
    createTexts(filenames, font);
}


void Menu::repositionText(sf::View &view, std::vector<sf::Text>& texts, std::vector<sf::RectangleShape>& relativeButtons) {

    sf::Vector2f v = sf::Vector2f (view.getSize().x* 0.25f, view.getSize().y * 0.1f);
    for (size_t i = 0; i < texts.size(); ++i) {
        sf::FloatRect textRect = texts[i].getLocalBounds();
        texts[i].setCharacterSize(static_cast<unsigned int>(v.y * 0.7f));
        texts[i].setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top + textRect.height / 2.0f);
        texts[i].setPosition(relativeButtons[i].getPosition().x + relativeButtons[i].getSize().x / 2.0f,
                             relativeButtons[i].getPosition().y + relativeButtons[i].getSize().y / 2.0f);
    }
}


void Menu::repositionButtons(sf::View& window, std::vector<sf::RectangleShape>& toChange){
            for (auto& button : toChange) {
        button.setSize(sf::Vector2f(window.getSize().x * 0.40f, window.getSize().y * 0.1f));
        }
        float windowWidth = window.getSize().x;
        float windowHeight = window.getSize().y;

        float buttonWidth = toChange[0].getGlobalBounds().width;
        float buttonHeight = toChange[0].getGlobalBounds().height;

        float totalHeight = toChange.size() * buttonHeight + (toChange.size() - 1) * 20;

        float startY = (windowHeight - totalHeight) / 2;
        float centerX = (windowWidth - buttonWidth) / 2;

        for (size_t i = 0; i < toChange.size(); ++i) {
            toChange[i].setPosition(centerX, startY + i * (buttonHeight + 20));
        }
    }



void Menu::setUpButtons(sf::Vector2f size, sf::Vector2f initialPos, int margin, int numberOfButtons) {
    if (!texture->loadFromFile("..//resources//s6.bmp")) {
        fmt::println("Failed loading button texture");

    }
    for(auto i = 0; i < numberOfButtons; i++) {
        auto button = sf::RectangleShape(size);
        button.setTexture(texture);
        button.setPosition(initialPos.x, initialPos.y + i * (size.y + margin));
        buttons.push_back(button);
    }



}
void Menu::reposition(sf::View& view){
    repositionButtons(view, buttons);
    repositionButtons(view,saves);
    repositionText(view, buttonTexts, buttons);
    repositionText(view, savesTexts, saves);

}

void Menu::render(sf::RenderWindow & render, sf::View& view) {
    reposition(view);
    if(isChoosing){
        for(const auto& v : saves){
            render.draw(v);
        }

        for(const auto& t : savesTexts){
            render.draw(t);
        }
    }else{
        for(const auto& b : buttons){
            render.draw(b);
        }
        for(const auto& t : buttonTexts){
            render.draw(t);
        }
    }



}

void Menu::makeTexts(sf::Font& font, std::vector<std::string> strings) {
    for(auto i = 0; i < buttons.size(); i++)
                {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(strings[i]);
                    text.setCharacterSize(20);
                    text.setFillColor(sf::Color::White);

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
                        game.gameState = State::GAME;
                    }
                    if(text == "Save"){

                        isChoosing = true;
                        sf::sleep(sf::milliseconds(100));
                    }
                    if(text == "Exit"){
                        game.gameState = State::MENU;
                    }

                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    isChoosing = false;
                }

            }
        }else {
            for(auto i = 0; i < saves.size(); i++){
                if(saves[i].getGlobalBounds().contains(vector.x, vector.y)){
                        if(not isDialog){
                            isChoosing = false;

                            auto str1 = std::string("");
                            std::string s ="./../resources/saves/" +savesTexts[i].getString();


                            showInputDialog("Provide new save name", str1);
                            try {
                                game.save(world,str1);
                            } catch (const std::system_error& e) {
                                std::cerr << e.what() << std::endl;
                            }
                            if(savesTexts[i].getString() != str1){
                                if(remove(s.c_str()) == 0){
                                    fmt::println("Deleted");
                                }else {
                                    fmt::println("error");
                                }
                            }
                            savesTexts[i] = createText(i,font, str1);

                            }
                    sf::sleep(sf::milliseconds(100));
                        }

                }
            }
        }

    }



void Menu::createTexts(const std::vector<std::string>& filenames, sf::Font &font){
    savesTexts.clear();
    auto i = 0;
    for(auto k= 0;k < filenames.size(); k++){
        i++;
        savesTexts.push_back(createText(k, font, filenames[k]));
    }
    while (i < 3){
        savesTexts.push_back(createText(i, font, "Empty"));
        i++;
    }
}

sf::Text Menu::createText(int i, sf::Font &font, const std::string& string){
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
void Menu::showInputDialog(const std::string & message, std::string & userInput) {
    sf::RenderWindow dialogWindow(sf::VideoMode(400, 200), "Input Dialog", sf::Style::Titlebar | sf::Style::Close);

    sf::Font font;
    if (!font.loadFromFile("./../resources/arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }
    sf::Text messageText;
    messageText.setFont(font);
    messageText.setString(message);
    messageText.setCharacterSize(24);
    messageText.setFillColor(sf::Color::White);
    messageText.setPosition(50, 30);

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(50, 100);

    while (dialogWindow.isOpen()) {
        sf::Event event;
        while (dialogWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                dialogWindow.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!userInput.empty()) {
                        userInput.pop_back();
                    }
                } else if (event.text.unicode == '\r') {
                    dialogWindow.close();
                } else {
                    userInput += event.text.unicode;
                }
                inputText.setString(userInput);
            }
        }

        dialogWindow.clear(sf::Color::Black);
        dialogWindow.draw(messageText);
        dialogWindow.draw(inputText);
        dialogWindow.display();
    }
}
