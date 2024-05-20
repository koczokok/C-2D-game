#include <iostream>
#include <SFML/Graphics.hpp>
#include "fmt/core.h"
#include "world.h"
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

    // Background
    sf::Texture background;
    if(!background.loadFromFile("C:\\Users\\pkury\\CLionProjects\\PJC-Game\\0.png")){
        return EXIT_FAILURE;
    }
    sf::Sprite backgroundSprite(background);

    // Player
    auto player = Character("dem.png",sf::Vector2f(0,0), sf::Vector2f(50,50), sf::Vector2f (16,16), sf::Vector2f(0,0), 20.f);

    //Enemy
    auto enemies = std::vector<Character *>();
    enemies.push_back(new Character("dem.png",sf::Vector2f(0,18), sf::Vector2f(100,100), sf::Vector2f (16,16), sf::Vector2f(0,0), 5.f));

    bool left, right, up, down;
    while(window.isOpen()){
        auto event = sf::Event();
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();

        }

        //Keyboard events
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            right = true;
        else
            right = false;
        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
            right = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            left = true;
        else
            left = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            up = true;
        else
            up = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            down = true;
        else
            down = false;
        player.shootTimer++;
        if(player.shootTimer > 10) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                player.projectiles.push_back(new Projectile("Chuj", player.characterSprite.getPosition(),
                                                                sf::Vector2f(-5 + player.velocity.x,
                                                                             0 + player.velocity.y)));
                player.shootTimer = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                player.projectiles.push_back(new Projectile("Chuj", player.characterSprite.getPosition(),
                                                                sf::Vector2f(0 + player.velocity.x,
                                                                             -5 + player.velocity.y)));
                player.shootTimer = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                player.projectiles.push_back(new Projectile("Chuj", player.characterSprite.getPosition(),
                                                                sf::Vector2f(0 + player.velocity.x,
                                                                             5 + player.velocity.y)));
                player.shootTimer = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                player.projectiles.push_back(new Projectile("Chuj", player.characterSprite.getPosition(),
                                                                sf::Vector2f(5 + player.velocity.x,
                                                                             0 + player.velocity.y)));
                player.shootTimer = 0;
            }
        }
        //Moving objects
        player.updateMovement(up, down, right, left);
        for(auto i : player.projectiles){
            i->circle.move(i->velocity);
        }
        for(auto e : enemies){
            auto velx = player.characterSprite.getPosition().x - e->characterSprite.getPosition().x;
            auto vely = player.characterSprite.getPosition().y - e->characterSprite.getPosition().y;
            e->characterSprite.move(velx/40,vely/40);
        }

        //Collisions
        for(auto p : player.projectiles){
            for(auto e : enemies){
                if(p->circle.getGlobalBounds().intersects(e->characterSprite.getGlobalBounds())){
                    fmt::println("{}", "Dead");
                    auto iter = std::ranges::find(enemies.begin(), enemies.end(), e);
                    enemies.erase(iter);
                    auto iter1 = std::ranges::find(player.projectiles, p);
                    player.projectiles.erase(iter1);
                }

            }

        }
        for(int i = 0; i < world.tiles.size(); i++){
            for(int j = 0; j < world.tiles[i].size(); j++){
                player.collide(world.tiles[i][j]);
                player.checkProjectileCollisions(world.tiles[i][j]);
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        //Drawing tiles
        for(auto & i : world.tiles){
            for(auto j : i){
                window.draw(j->sprite);
            }
        }
        //Drawing projectiles
        for(auto i : player.projectiles){
            window.draw(i->circle);
        }
        for(auto e : enemies)
            window.draw(e->characterSprite);

        window.draw(player.characterSprite);
        window.display();
    }
}
