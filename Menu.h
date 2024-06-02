//
// Created by pkury on 01/06/2024.
//
#pragma once
#include <SFML/Graphics.hpp>
#include "GameStates.h"
#include "game.h"

#ifndef PJC_GAME_MENU_H
#define PJC_GAME_MENU_H
struct Menu {

    Menu(sf::Font&, sf::Vector2f size, sf::Vector2f initialPos, int margin, int numberOfButtons, std::vector<std::string>);
    void setUpButtons(sf::Vector2f size, sf::Vector2f initialPos, int margin, int numberOfButtons);
    void render(sf::RenderWindow&);
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
    sf::Texture* texture;
    void makeTexts(sf::Font& , std::vector<std::string>);
    void checkButtonClick(sf::Vector2i, Game&);

};
#endif //PJC_GAME_MENU_H
