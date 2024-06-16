
#include <iostream>
#include <SFML/Graphics.hpp>
#include "fmt/core.h"
#include "Game/world.h"
#include "Menus/Menu.h"
#include "Game/game.h"
#include "Game/HUD.h"
#include "Menus/mainMenu.h"
#include "Game/gameWon.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


int main() {
    auto game = Game();
    World world = World(false, false);

    int shootTimer = 0;
    auto view = sf::View();
    view.reset(sf::FloatRect(0, 0, 400, 240));
    auto window = sf::RenderWindow(
            sf::VideoMode({400, 240}), "Test",
            sf::Style::Default, sf::ContextSettings(0, 0, 8)
    );
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("./../resources/arial.ttf")) {
        fmt::println("Failed loading font");
    }
    // Background
    sf::Texture background;
    if (!background.loadFromFile("./../resources/backGrounds.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite backgroundSprite(background);
    backgroundSprite.setTextureRect(sf::IntRect (0,0,view.getSize().x,view.getSize().y));
    auto scaleSpriteToWindow = [&backgroundSprite, &background](sf::RenderWindow& window) {
        sf::Vector2u windowSize = window.getSize();
        sf::Vector2u textureSize = background.getSize();
        float scaleX = static_cast<float>(windowSize.x + 300) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
        float scale = std::max(scaleX, scaleY);
        backgroundSprite.setScale(scale, scale);
        backgroundSprite.setOrigin(textureSize.x / 2.f, textureSize.y / 2.f);
        backgroundSprite.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
    };
    auto hud = HUD(window, world.player->hearts);
    GameWon gameWon = GameWon(font, window);

    auto settings = Menu(font, sf::Vector2f(150, 25), sf::Vector2f(125, 50), 10, 3,
                         std::vector<std::string>{"Resume", "Save", "Exit"});
    auto menu = MainMenu(font, sf::Vector2f(150, 25), sf::Vector2f(125, 100), 10, 3,
                         std::vector<std::string>{"New Game", "Load from save", "Quit"});
    bool left, right, up, down;
    while (window.isOpen()) {
        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                                window.close();
            }


        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            menu.checkButtonClick(sf::Mouse::getPosition(window), game, world);
          settings.checkButtonClick(sf::Mouse::getPosition(window), game, world, window, font);
        }

        if(event.type == sf::Event::Resized){






        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)){

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
           game.gameState = State::PAUSE;

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
        world.player->shootTimer++;
        if (world.player->shootTimer > 15) {
            auto global = world.player->characterSprite.getGlobalBounds();
            auto pos = sf::Vector2f (global.left + (global.width / 2), global.top + (global.height / 2));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                world.player->projectiles.push_back(new Projectile( pos,
                                                            sf::Vector2f(-5 + world.player->velocity.x * 0.1f ,0 + world.player->velocity.y * 0.1f)));
                world.player->shootTimer = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                world.player->projectiles.push_back(new Projectile( pos,
                                                            sf::Vector2f(0 + world.player->velocity.x * 0.1f ,
                                                                         -5 + world.player->velocity.y * 0.1f)));
                world.player->shootTimer = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                world.player->projectiles.push_back(new Projectile(pos,
                                                            sf::Vector2f(0+world.player->velocity.x * 0.1f ,
                                                                         5 + world.player->velocity.y * 0.1f)));
                world.player->shootTimer = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                world.player->projectiles.push_back(new Projectile(pos,
                                                            sf::Vector2f(5 +world.player->velocity.x * 0.1f,
                                                                         0+ world.player->velocity.y * 0.1f )));
                world.player->shootTimer = 0;
            }
        }




        if(game.gameState == State::QUIT){
            window.close();
        }

        if(game.gameState == State::WON){
            view.reset(sf::FloatRect(0, 0, 400, 240));
            window.setView(view);
            window.clear();
            scaleSpriteToWindow(window);
            window.draw(backgroundSprite);
            gameWon.renderWon(window);
            window.display();
            continue;
        }

        if(game.gameState == State::PAUSE){
            view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
            window.setView(view);
            window.clear();
           scaleSpriteToWindow(window);
            window.draw(backgroundSprite);
            settings.render(window, view);
            window.display();
            continue;
        }

        if(game.gameState == State::MENU){
            view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
            window.setView(view);
            window.clear();
            scaleSpriteToWindow(window);
            window.draw(backgroundSprite);
            menu.render(window, view);
            window.display();
            continue;
        }
        if(game.gameState == State::GAME) {
            view.reset(sf::FloatRect(0, 0, 400, 240));
            world.player->updateMovement(up, down, right, left);
            view.setCenter(world.player->characterSprite.getPosition());
            window.setView(view);
            window.clear();




            world.renderMain(window, shootTimer, game);
            window.draw(world.player->characterSprite);
            world.player->playerRender(window, game);
            hud.setHudPosition(window, world.player->hearts);
            shootTimer++;

            window.display();
            continue;
        }

    }


}

