//
// Created by pkury on 12/06/2024.
//

#include "HUD.h"
#include "fmt/core.h"

HUD::HUD(sf::RenderWindow &window, int &player_hearts) {

    heartsTextures = std::vector<sf::Texture>(5);
    for(auto i = 0; i < 5;i++){
       heartsTextures.at(i).loadFromFile("C:\\Users\\pkury\\CLionProjects\\PJC-Game\\resources\\Hearts\\" + std::to_string(i+1) + ".png");
    }
    hearts.setTextureRect(sf::IntRect(0,0,80,16));
    hearts.setTexture(heartsTextures.at(4));
    setHudPosition(window, player_hearts);
}

void HUD::setHudPosition(sf::RenderWindow & window, int & player_hearts) {
    if(player_hearts > 0){
        hearts.setTexture(heartsTextures.at((player_hearts) -1));
    }

    sf::View hudView = window.getView();

    hearts.setPosition(hudView.getCenter().x - (hudView.getSize().x / 2) + 5,hudView.getCenter().y - (hudView.getSize().y / 2 ) + 5);
    window.draw(hearts);
}


