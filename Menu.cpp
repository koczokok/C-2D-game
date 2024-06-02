//
// Created by pkury on 01/06/2024.
//

#include "Menu.h"
#include "fmt/core.h"


Menu::Menu(sf::Font& font ,sf::Vector2f size, sf::Vector2f initialPos, int margin, int numberOfButtons, std::vector<std::string> buttonNames) : texture(new sf::Texture()){



    setUpButtons(size, initialPos, margin, numberOfButtons);
    makeTexts(font, buttonNames);
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

        for(auto b : buttons){
            render.draw(b);
        }
        for(auto t : buttonTexts){
            render.draw(t);
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

                    // Center the text within the rectangle
                    sf::FloatRect textRect = text.getLocalBounds();
                    text.setOrigin(textRect.left + textRect.width / 2.0f,
                                   textRect.top + textRect.height / 2.0f);
                    text.setPosition(buttons[i].getPosition().x + buttons[i].getSize().x / 2.0f,
                                     buttons[i].getPosition().y + buttons[i].getSize().y / 2.0f);
                    buttonTexts.push_back(text);
                }
}





void Menu::checkButtonClick(sf::Vector2i vector, Game& game) {
        for(auto i = 0; i < buttons.size(); i++){
            if(buttons[i].getGlobalBounds().contains(vector.x, vector.y)){
                auto text = buttonTexts[i].getString();
                if(text == "New Game")
                    game.gameState = State::GAME;
                if(text == "Load from save")
                    game.gameState = State::GAME;
                if(text == "Quit")
                    game.gameState = State::QUIT;
                if(text == "Resume")
                    game.gameState = State::GAME;
                if(text == "Save")
                    game.gameState = State::GAME;
                if(text == "Exit")
                    game.gameState = State::QUIT;
            }
        }
}




