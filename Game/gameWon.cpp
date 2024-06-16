//
// Created by pkury on 15/06/2024.
//

#include "gameWon.h"
#include "SFML/Graphics.hpp"
#include "fmt/core.h"

GameWon::GameWon(sf::Font &font, sf::RenderWindow& renderWindow){
    text.setFont(font);
    text.setString("Congrats you finished this epic bombastic game \n Arrivederci and thank you for playing! ");
    text.setCharacterSize(17);
    text.setFillColor(sf::Color::White);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition( renderWindow.getSize().x / 2.0f,
                      renderWindow.getSize().y / 2.0f);


}

void GameWon::renderWon(sf::RenderWindow& renderWindow){
    renderWindow.draw(text);
}