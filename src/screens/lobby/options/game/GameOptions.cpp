#include <iostream>
#include "GameOptions.h"

GameOptions::GameOptions(sf::RenderWindow* window) : Options(window) {
    _players_selector = PlayersSelector(_window);
    _rounds_selector = RoundsSelector(_window);
}

void GameOptions::input(const sf::Event &event) {

    if (event.type == sf::Event::KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            _current_selector = (_current_selector + 2 + 1) % 2; // TODO : create a const, currently 2
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            _current_selector  = (_current_selector + 2 - 1) % 2;
        }
    }

    if (_current_selector == 0){
        _players_selector.input(event);
    }
    else {
        _rounds_selector.input(event);
    }
}

void GameOptions::update(float dt_as_seconds) {
    _players_selector.update(dt_as_seconds);
    _rounds_selector.update(dt_as_seconds);
}


void GameOptions::draw() {
    _players_selector.draw();
    _rounds_selector.draw();
}

bool GameOptions::allDone() const {
    return true;
}

unsigned int GameOptions::getNumberOfPlayers() {
    return _players_selector.getCurrentPlayers();
}

unsigned int GameOptions::getNumberOfRounds() {
    return _rounds_selector.getCurrentRounds();
}


