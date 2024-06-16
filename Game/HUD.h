//
// Created by pkury on 12/06/2024.
//

#ifndef PJC_GAME_HUD_H
#define PJC_GAME_HUD_H

#include "SFML/Graphics.hpp"

class HUD{


    std::vector<sf::Texture> heartsTextures;

    sf::Sprite hearts;

public:

    HUD(sf::RenderWindow &window, int &player_hearts);

    void setHudPosition(sf::RenderWindow&, int&);
};

#endif //PJC_GAME_HUD_H
