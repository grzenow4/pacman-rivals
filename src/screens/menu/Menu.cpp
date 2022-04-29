#include "Menu.h"

#include <iostream>

const unsigned int Menu::OPTIONS_NUM = 2;
const float Menu::SPACE_BETWEEN = 200.f;

Menu::Menu(sf::RenderWindow* window, Screen* current_screen) {
    _window = window;
    _view.reset(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));

    _current_screen = current_screen;

    if (!_font.loadFromFile("../assets/fonts/capuche/Capuche Trial.otf")) {
        std::cerr << "Failed to load _menu_font.\n";
        exit(1);
    }

    _options = std::vector<sf::Text>(OPTIONS_NUM);
    _options[0].setString("New Game");
    _options[1].setString("Settings");
    // option_offset - vertical distance from screen's center of current option
    float option_offset = -SPACE_BETWEEN * (OPTIONS_NUM / 2);
    for (int i = 0; i < OPTIONS_NUM; i++) {
        _options[i].setFont(_font);
        _options[i].setCharacterSize(80);
        _options[i].setFillColor(sf::Color::White);
        sf::FloatRect option_position = _options[i].getGlobalBounds();
        _options[i].setOrigin(option_position.width / 2, option_position.height / 2);
        _options[i].setPosition(_view.getCenter().x, _view.getCenter().y + option_offset);
        option_offset += SPACE_BETWEEN;
    }
}

void Menu::input() {
    sf::Event event;

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                _window->close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                *_current_screen = GAME;
            }
        }
    }

    // TODO
}

void Menu::update(float dt_as_seconds) {
    // TODO
}

void Menu::draw() {
    _window->clear(sf::Color::Black);
    _window->setView(_view);

    for (int i = 0; i < OPTIONS_NUM; i++) {
        _options[i].setFont(_font); // why is it needed? 100 points question
        _window->draw(_options[i]);
    }

    _window->display();
}