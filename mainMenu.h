//
// Created by pkury on 13/06/2024.
//

#ifndef PJC_GAME_MAINMENU_H
#define PJC_GAME_MAINMENU_H

#include "Menu.h"
#include "saveDialog.h"

class MainMenu : Menu{
    std::vector<sf::Text> savesTexts;
public:
    std::vector<sf::RectangleShape> saves;
    bool isDialogOpen;
    bool isChoosingSave;

    void render(sf::RenderWindow&) override;
    void checkButtonClick(sf::Vector2i, Game&, World&, sf::RenderWindow&);
    MainMenu(sf::Font &, sf::Vector2f size, sf::Vector2f initialPos, int margin, int numberOfButtons,
             std::vector<std::string>);





    void createTexts(const std::vector<std::string> &filenames, sf::Font &font);

    sf::Text createText(int i, sf::Font &font, std::string);
};
#endif //PJC_GAME_MAINMENU_H
