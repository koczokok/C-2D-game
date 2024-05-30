#include <iostream>
#include <SFML/Graphics.hpp>
#include "fmt/core.h"
#include "world.h"
#include "character.h"
#include "Enemy/enemy.h"
#include "Enemy/Casual.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
int main() {
   auto world = World();
    auto shootTimer = 0;
    auto view = sf::View();
    view.reset(sf::FloatRect(0, 0, 400, 240));
    auto window = sf::RenderWindow(
            sf::VideoMode({400,240}), "Test",
            sf::Style::Default, sf::ContextSettings(0,0,8)
            );
    window.setFramerateLimit(60);

    // Background
    sf::Texture background;
    if(!background.loadFromFile("C:\\Users\\pkury\\CLionProjects\\PJC-Game\\resources\\0.png")){
        return EXIT_FAILURE;
    }
    sf::Sprite backgroundSprite(background);
    // Player
    auto player = Character("dem.png",sf::Vector2f(0,0), sf::Vector2f(200,440), sf::Vector2f (16,16), sf::Vector2f(0,0), 20.f, 5);

    //Enemy



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
//        for(auto e : enemies){
//            e->shootTimer++;
//        }
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


        player.updateMovement(up, down, right, left);
        view.setCenter(player.characterSprite.getPosition());

        //Moving objects


        player.movePlayerProjectiles();


       world.checkPlayerHit(player);

        if(player.hearts < 0){
            fmt::println("{}", "dead");
            window.close();
        }
        for(auto  const& tile : world.tiles){
            for(auto  const& j : tile){
                window.draw(j->sprite);
                player.collide(j);
                player.checkProjectileCollisions(j);
            }
        }
        window.setView(view);
        window.clear();
        window.draw(backgroundSprite);
        //Drawing tiles
        world.checkEnemyCollisions();
        //Drawing projectiles
        for(auto const& i : player.projectiles){

            window.draw(i->circle);
        }
        world.checkEnemyCollisionProjectile(player);


        for(auto& r : world.rooms){

            if(r->enemies.size() > 0){
                for(auto& e : r->enemies){
                    if(r->isActive) {
                        window.draw(e->characterSprite);
                        e->move();
                }
            }}
        }
        for(auto& r : world.rooms){
            if(r->bounds.intersects(player.characterSprite.getGlobalBounds()) && !r->enemies.empty()){
                r->isActive = true;
                for(auto t : r->exits){
                    t->isPassable= false;
                }
            }else if(r->enemies.empty())
                r->deactive();
        }
        shootTimer++;
        if(shootTimer > 40){

            for(auto const& r : world.rooms){
                if(r->isActive) {
                    for (auto &e: r->enemies) {
                        world.projectiles.push_back(e->shoot(""));
                        shootTimer = 0;
                    }
                }
            }
        }
        for(auto const& p : world.projectiles){
            window.draw(p->circle);
            p->circle.move(p->velocity);
        }

        window.draw(player.characterSprite);
        window.display();
    }
}
