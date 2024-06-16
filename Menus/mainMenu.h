//
// Created by pkury on 13/06/2024.
//

#ifndef PJC_GAME_MAINMENU_H
#define PJC_GAME_MAINMENU_H

#include "Menu.h"


class MainMenu : public Menu{

public:



    void checkButtonClick(sf::Vector2i, Game &, World &);
    MainMenu(sf::Font &, sf::Vector2f size, sf::Vector2f initialPos, int margin, int numberOfButtons,
             std::vector<std::string>);






};
#endif //PJC_GAME_MAINMENU_H
