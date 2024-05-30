//
// Created by pkury on 27/05/2024.
//
#include <SFML/Graphics.hpp>
#ifndef PJC_GAME_GAME_H
#define PJC_GAME_GAME_H
class Game
{
private:
        sf::RenderWindow* window;
        void initWindow();
        void initVariables();

        sf::VideoMode videoMode;

public:
        //Constructor / Destructors
        Game();
        virtual ~Game();

        //functions
        void update();
        void render();
};

#endif //PJC_GAME_GAME_H
