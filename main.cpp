#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "fmt/core.h"
#include "world.h"
#include <fstream>
#include "character.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
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
    auto character2 = Character("dem.png", sf::Vector2f(50,50), sf::Vector2f (16,16), sf::Vector2f(0,0), 5.f);
    if(!character.loadFromFile("../dem.png")){
        return EXIT_FAILURE;
    }
    sf::Sprite characterSprite(character);
    characterSprite.setTextureRect(sf::IntRect(0,0,16,16));

    characterSprite.setPosition(50,50);
    float dt;
    sf::Clock dt_clock;
    bool left, right, up, down;
    while(window.isOpen()){
        dt = dt_clock.restart().asSeconds();
        auto event = sf::Event();
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();

        }

//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && characterSprite.getPosition().x < window.getSize().x - 16)
//            character2.characterSprite.move(3,0.f);
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && characterSprite.getPosition().x > 0)
//            character2.characterSprite.move(-5,0.f);
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && characterSprite.getPosition().y > 0)
//            character2.characterSprite.move(0,-5);
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&  characterSprite.getPosition().y < window.getSize().y - 16)
//            character2.characterSprite.move(0,5);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && character2.characterSprite.getPosition().x < window.getSize().x - 16)
            right = true;
        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && character2.characterSprite.getPosition().x < window.getSize().x - 16))
            right = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && character2.characterSprite.getPosition().x > 0)
            left = true;
        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && character2.characterSprite.getPosition().x > 0))
            left = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && character2.characterSprite.getPosition().x < window.getSize().x - 16)
            up = true;
        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && character2.characterSprite.getPosition().x < window.getSize().x - 16))
            up = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && character2.characterSprite.getPosition().x > 0)
            down = true;
        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && character2.characterSprite.getPosition().x > 0))
            down = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            character2.projectiles.push_back(new Projectile("Chuj", sf::Vector2f(50,50), sf::Vector2f(-0.1,0)));
        character2.updateMovement(up, down, right, left);
        character2.characterSprite.move(character2.velocity);
        character2.updatePosition(1,1,1,1);
        for(auto i : character2.projectiles){
            ;

            fmt::println("{}, {}", i->position.x, i->position.y);
        }
        for(int i = 0; i < world.tiles.size(); i++){
            for(int j = 0; j < world.tiles[i].size(); j++){
                character2.collide(world.tiles[i][j]);
            }
        }
//        if(character2.characterSprite.getGlobalBounds().intersects(world.tiles[1][1]->sprite.getGlobalBounds())){
//            fmt::println("{}", "Collides");
//            character2.velocity = sf::Vector2f(0,0);
//        }
            window.clear();
        window.draw(backgroundSprite);
            for(auto & i : world.tiles){
                for(auto j : i){
                    window.draw(j->sprite);
                }
            }
            for(auto i : character2.projectiles){
                window.draw(i->circle);
            }
        window.draw(character2.characterSprite);

        window.draw(characterSprite);
        window.display();
    }
}
