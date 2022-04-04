#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "../texture-holder/TextureHolder.h"
#include "../level-manager/LevelManager.h"
#include "../characters/player/Pacman.h"
#include "../coins/Coin.h"

class GameEngine {

private:

    sf::RenderWindow _window;

    sf::View _main_view; // view used for drawing game (map and characters)

    TextureHolder _texture_holder;

    LevelManager _level_manager;

    std::vector<std::shared_ptr<Ghost>> _ghosts;

    std::vector<std::shared_ptr<Pacman>> _pacmans;

    std::unordered_map<int, Coin> _coins;

    bool _new_map_needed;

    void input();

    void update(float dt_as_seconds);

    void draw();

public:

    GameEngine();

    void run();

};
