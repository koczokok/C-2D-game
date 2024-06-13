//
// Created by pkury on 13/06/2024.
//

#ifndef PJC_GAME_SAVEDIALOG_H
#define PJC_GAME_SAVEDIALOG_H
#include <SFML/Graphics.hpp>
#include "game.h"


class SaveDialog{
public:
    SaveDialog();
    static std::string createDialog(Game&, World&, std::string);
};

#endif //PJC_GAME_SAVEDIALOG_H
