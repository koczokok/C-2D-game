#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "fmt/core.h"
#include "world.h"
#include <fstream>
int main() {
   auto world = World();



    auto window = sf::RenderWindow(
            sf::VideoMode({400,240}), "Test",
            sf::Style::Default, sf::ContextSettings(0,0,8)
            );
    window.setFramerateLimit(60);
    auto shape = sf::RectangleShape(sf::Vector2f(100.f,100.f));
    shape.setPosition(400,300);

    shape.setFillColor(sf::Color::Magenta);

    sf::Texture background;
    if(!background.loadFromFile("C:\\Users\\pkury\\CLionProjects\\PJC-Game\\0.png")){
        return EXIT_FAILURE;
    }
    sf::Sprite backgroundSprite(background);
    sf::Texture character;

    if(!character.loadFromFile("../dem.png")){
        return EXIT_FAILURE;
    }
    sf::Sprite characterSprite(character);
    characterSprite.setTextureRect(sf::IntRect(0,0,16,16));

    characterSprite.setPosition(50,50);

    while(window.isOpen()){

        auto event = sf::Event();
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();

        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && characterSprite.getPosition().x < window.getSize().x - 16)
            characterSprite.move(3,0.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && characterSprite.getPosition().x > 0)
            characterSprite.move(-5,0.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && characterSprite.getPosition().y > 0)
            characterSprite.move(0,-5);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&  characterSprite.getPosition().y < window.getSize().y - 16)
            characterSprite.move(0,5);


        for(int i = 0; i < world.tiles.size(); i++){
            for(int j = 0; j < world.tiles[i].size(); j++){
                if((world.tiles[i][j]->sprite.getGlobalBounds().intersects(characterSprite.getGlobalBounds())) && !world.tiles[i][j]->isPassable){
                    fmt::println("{}", "Colision");

                }
            }
        }
//
            window.clear();
        window.draw(backgroundSprite);
            for(auto & i : world.tiles){
                for(auto j : i){
                    window.draw(j->sprite);

                }
            }



        window.draw(characterSprite);
        window.display();
    }
}
