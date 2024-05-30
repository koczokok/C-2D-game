//
// Created by pkury on 27/05/2024.
//


#include "Game.h"

void Game::initWindow() {
    this->videoMode.height= 240;
    this->videoMode.width = 400;
    this->window = new sf::RenderWindow(
            this->videoMode, "Test",
            sf::Style::Default, sf::ContextSettings(0,0,8)
    );
}

void Game::initVariables() {
    this->window = nullptr;
}

Game::Game() {
    initVariables();
    initWindow();
}

Game::~Game() {
    delete this->window;
}

void Game::update() {

}

void Game::render() {

}

