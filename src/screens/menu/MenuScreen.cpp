#include "MenuScreen.h"
#include "../../sound-manager/SoundManager.h"
#include "../../../include/random.h"

#include <iostream>

const unsigned int MenuScreen::OPTIONS_NUM = 3;
const float MenuScreen::SPACE_BETWEEN = 200.f;

MenuScreen::MenuScreen(sf::RenderWindow* window, ScreenName* current_screen) : Screen(window, current_screen) {
    _view.reset(sf::FloatRect(0, 0, (float)sf::VideoMode::getDesktopMode().width,
                                    (float)sf::VideoMode::getDesktopMode().height));

    if (!_font.loadFromFile("../assets/fonts/Emulogic-zrEw.ttf")) {
        std::cerr << "Failed to load _font in MenuScreen constructor.\n";
        exit(1);
    }

    _current_option = 0;
    _options = std::vector<sf::Text>(OPTIONS_NUM);
    _options[0].setString("New Game");
    _options[1].setString("Settings");
    _options[2].setString("Controls");
    // option_offset - vertical distance from screen's center of current option
    float option_offset = -SPACE_BETWEEN * (OPTIONS_NUM / 2.f);
    for (int i = 0; i < OPTIONS_NUM; i++) {
        _options[i].setFont(_font);
        _options[i].setCharacterSize(80);
        _options[i].setFillColor(sf::Color::White);
        sf::FloatRect option_position = _options[i].getGlobalBounds();
        _options[i].setOrigin(option_position.width / 2, option_position.height / 2);
        _options[i].setPosition(_view.getCenter().x, _view.getCenter().y + option_offset);
        option_offset += SPACE_BETWEEN;
    }

    for (int i = 0; i < _number_of_characters; ++i) {
        int direction = random(0, 3);
        _menu_characters.emplace_back(std::make_shared<MenuCharacter>
                (random(0, sf::VideoMode::getDesktopMode().width - 1), random(0, sf::VideoMode::getDesktopMode().height - 1), direction));
    }
}

void MenuScreen::initialise(bool restart_music) {
    _current_option = 0;
    if (restart_music) {
        SoundManager::playMusic();
    }
}

void MenuScreen::input() {
    sf::Event event{};

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            for (int i = 0; i < OPTIONS_NUM; i++) {
                _options[i].setFillColor(sf::Color::White);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                _window->close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                if (_current_option == 0) {
                    *_current_screen = LOBBY;
                }
                if (_current_option == 1) {
                    *_current_screen = SETTINGS;
                }
                if (_current_option == 2) {
                    *_current_screen = CONTROLS;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                _current_option = (_current_option + OPTIONS_NUM + 1) % OPTIONS_NUM;
                _options[_current_option].setFillColor(sf::Color::Red);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                _current_option = (_current_option + OPTIONS_NUM - 1) % OPTIONS_NUM;
                _options[_current_option].setFillColor(sf::Color::Red);
            }
        }
    }
}


void MenuScreen::update(float dt_as_seconds) {
    for (auto character : _menu_characters) {
        character->update(dt_as_seconds);
    }
}

void MenuScreen::draw() {
    _window->clear(sf::Color::Black);
    _window->setView(_view);

    _options[_current_option].setFillColor(sf::Color::Red);

    for (auto character : _menu_characters) {
        _window->draw(character->getSprite());
    }

    for (int i = 0; i < OPTIONS_NUM; i++) {
        _options[i].setFont(_font);
        _window->draw(_options[i]);
    }

    _window->display();
}
