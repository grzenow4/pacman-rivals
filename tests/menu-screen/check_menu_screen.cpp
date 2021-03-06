#include "../../src/screens/menu/MenuScreen.h"
#include "../../src/texture-holder/TextureHolder.h"
#include "../../src/sound-manager/SoundManager.h"
#include "../../include/err.h"

#include <SFML/Graphics.hpp>

int main() {
    TextureHolder textureHolder;
    SoundManager soundManager;

    sf::Clock clock;

    sf::RenderWindow window(
        sf::VideoMode(sf::VideoMode::getDesktopMode().width,
                      sf::VideoMode::getDesktopMode().height),
        "Pacman Rivals", sf::Style::Fullscreen
    );

    ScreenName current_screen = MENU;
    MenuScreen menu(&window, &current_screen);

    menu.input();
    menu.update(clock.restart().asSeconds());
    err::checkEqual(MENU, current_screen);
}
