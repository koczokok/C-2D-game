//
// Created by pkury on 13/06/2024.
//

#ifndef PJC_GAME_CHOOSESAVE_H
#define PJC_GAME_CHOOSESAVE_H
#include <SFML/Graphics.hpp>
#include "world.h"
#include "game.h"

class ChooseSave{
public:
//    Game&, World&
    ChooseSave(Game&, World&);
    std::string createDialog(Game&, World&, int);
};
#endif //PJC_GAME_CHOOSESAVE_H
