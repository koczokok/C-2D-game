
#include <iostream>
#include <SFML/Graphics.hpp>
#include "fmt/core.h"
#include "world.h"
#include "Menu.h"
#include "game.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
int main() {
    auto game = Game();
    World world = World(false, false);
    auto shootTimer = 0;

    auto view = sf::View();
    view.reset(sf::FloatRect(0, 0, 400, 240));
    auto window = sf::RenderWindow(
            sf::VideoMode({400, 240}), "Test",
            sf::Style::Default, sf::ContextSettings(0, 0, 8)
    );
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\pkury\\CLionProjects\\PJC-Game\\resources\\arial.ttf")) {
        fmt::println("Fuckk");
    }
    // Background
    sf::Texture background;
    if (!background.loadFromFile("C:\\Users\\pkury\\CLionProjects\\PJC-Game\\resources\\back.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite backgroundSprite(background);
    // Player


    //Enemy

    auto settings = Menu(font, sf::Vector2f(150,25), sf::Vector2f (125, 50), 10, 4, std::vector<std::string>{"Resume", "Save", "Options","Exit"});
    auto menu = Menu(font, sf::Vector2f(150,25), sf::Vector2f(125,100), 10, 3, std::vector<std::string>{"New Game", "Load from save", "Quit"});
    bool left, right, up, down;
    while (window.isOpen()) {
        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
          menu.checkButtonClick(sf::Mouse::getPosition(window), game, world, player);
          settings.checkButtonClick(sf::Mouse::getPosition(window), game, world, player);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)){
            game.loadSave("example.txt", world, player);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
//           game.gameState = State::PAUSE;
game.save(world, player);
        }
        //Keyboard events
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            right = true;
        else
            right = false;
        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
            right = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            left = true;
        else
            left = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            up = true;
        else
            up = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            down = true;
        else
            down = false;
        player.shootTimer++;
        if (player.shootTimer > 10) {
            auto global = player.characterSprite.getGlobalBounds();
            auto pos = sf::Vector2f (global.left + (global.width / 2), global.top + (global.height / 2));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                player.projectiles.push_back(new Projectile("Chuj", pos,
                                                            sf::Vector2f(-5 ,0)));
                player.shootTimer = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                player.projectiles.push_back(new Projectile("Chuj", pos,
                                                            sf::Vector2f(0 ,
                                                                         -5 )));
                player.shootTimer = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                player.projectiles.push_back(new Projectile("Chuj",pos,
                                                            sf::Vector2f(0 ,
                                                                         5 )));
                player.shootTimer = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                player.projectiles.push_back(new Projectile("Chuj", pos,
                                                            sf::Vector2f(5,
                                                                         0 )));
                player.shootTimer = 0;
            }
        }



//        for(auto r : world.rooms){
//            fmt::println("{}", r->isActive);
//        }
        //Moving objects
        if(game.gameState == State::QUIT){
            window.close();
        }

        if(game.gameState == State::PAUSE){
            view.reset(sf::FloatRect(0, 0, 400, 240));
            window.setView(view);
            window.clear();
            window.draw(backgroundSprite);
            settings.render(window);
            window.display();
            continue;
        }

        if(game.gameState == State::MENU){
            window.clear();
            window.draw(backgroundSprite);
            menu.render(window);
            window.display();
            continue;
        }
        if(game.gameState == State::GAME) {
            player.updateMovement(up, down, right, left);
            view.setCenter(player.characterSprite.getPosition());
            window.setView(view);
            window.clear();
            world.renderMain(window, player, shootTimer);
            shootTimer++;
            player.playerRender(window, game);
            for(auto s : world.rooms[4]->exits){
                fmt::println("{} {}",s->pos.x, s->pos.y);

            }
            window.display();
            continue;
        }

    }


}