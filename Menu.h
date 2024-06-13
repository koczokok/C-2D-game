//
// Created by pkury on 01/06/2024.
//

#ifndef PJC_GAME_MENU_H
#define PJC_GAME_MENU_H
#include <SFML/Graphics.hpp>
#include "GameStates.h"
#include "game.h"
#include "saveDialog.h"


struct Menu {
    bool isChoosing;
    bool isDialog;
    SaveDialog dialog;
    std::vector<sf::RectangleShape> saves;
    std::vector<sf::Text> savesTexts;

    void createTexts(const std::vector<std::string> &filenames, sf::Font &font);

    sf::Text createText(int i, sf::Font &font, std::string);
    Menu(sf::Font&, sf::Vector2f size, sf::Vector2f initialPos, int margin, int numberOfButtons, std::vector<std::string>);
    void setUpButtons(sf::Vector2f size, sf::Vector2f initialPos, int margin, int numberOfButtons);
    virtual void render(sf::RenderWindow&);
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
    sf::Texture* texture;
    void makeTexts(sf::Font& , std::vector<std::string>);


    virtual void
    checkButtonClick(sf::Vector2i vector, Game &game, World &world, sf::RenderWindow &renderWindow, sf::Font &font);
};
#endif //PJC_GAME_MENU_H
