#pragma once

#include <SFML/Graphics.hpp>

#include "../Screen.h"

class MenuScreen : Screen {

private:

    sf::View _view;

    static const unsigned int OPTIONS_NUM;
    static const float SPACE_BETWEEN; // vertical distance between 2 options
    std::vector<sf::Text> _options;

    sf::Font _font;

public:

    MenuScreen() = default;

    MenuScreen(sf::RenderWindow* window, ScreenName* current_screen);

    void input() override;

    void update(float dt_as_seconds) override;

    void draw() override;

};