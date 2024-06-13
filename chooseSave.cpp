//
// Created by pkury on 13/06/2024.
//

#include "chooseSave.h"
#include "fmt/core.h"
#include "fmt/std.h"
#include "saveDialog.h"
#include <filesystem>
ChooseSave::ChooseSave(Game & game, World & world) {
    int i = 0;
    for(const auto& entry : std::filesystem::directory_iterator("./saves")){
        if(std::filesystem::is_regular_file(entry)){
            fmt::println("{}", entry.path().filename());
            i++;
        }

    }
    createDialog(game, world,i );

}

std::string ChooseSave::createDialog(Game & game, World & world, int numberOfSaves) {
    sf::RenderWindow dialog(sf::VideoMode(400, 200), "Dialog");

    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\pkury\\CLionProjects\\PJC-Game\\resources\\arial.ttf")) {

    }
    sf::Texture* texture;
    if (!texture->loadFromFile("..//resources//s6.bmp")) {
    }
    auto vec = std::vector<sf::RectangleShape>();
    for(auto i = 0; i < 3;i++){
        auto r = sf::RectangleShape(sf::Vector2f (300,40));
        r.setPosition(50,20 + 60 *i);
        r.setTexture(texture);
        vec.push_back(r);
    }


    // Dialog event loop
    while (dialog.isOpen()) {
        sf::Event event;
        while (dialog.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                dialog.close();
            }
        }
        for(sf::RectangleShape r : vec){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(sf::FloatRect(r.getPosition().x, r.getPosition().y, 200,50).contains(sf::Mouse::getPosition(dialog).x, sf::Mouse::getPosition(dialog).y)){
                    fmt::println("Chhose");
//                    SaveDialog(game, world);
                    dialog.close();
                }
//                if(button.getGlobalBounds().contains(sf::Mouse::getPosition(dialog).x, sf::Mouse::getPosition(dialog).y)){
//                    fmt::println("{}", "kilk");
//                }
            }
        }

        dialog.clear();
        for(sf::RectangleShape r : vec){
            dialog.draw(r);
        }

        dialog.display();
    }
}
