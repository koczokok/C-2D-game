//
// Created by pkury on 15/06/2024.
//

#ifndef PJC_GAME_GAMEWON_H
#define PJC_GAME_GAMEWON_H

#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class GameWon{

    sf::Text text;

public:
    GameWon(sf::Font &font, sf::RenderWindow &renderWindow);

    void renderWon(sf::RenderWindow &renderWindow);
};

#endif //PJC_GAME_GAMEWON_H
