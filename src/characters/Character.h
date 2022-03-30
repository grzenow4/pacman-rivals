#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "../map/Map.h"
#include "../../include/game_constants.h"

class Character {

protected:

    float _speed = 10;

    sf::Sprite _sprite{};

    std::shared_ptr<Map> _map;

    enum Direction {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        STOP
    };

    Direction _direction;

public:

    Character(sf::Sprite sprite, std::shared_ptr<Map> map);

    sf::FloatRect getPosition();

    sf::Sprite &getSprite();

    virtual void update(float dt_as_seconds) = 0;

private:

    bool reachedNewTile(float dt_as_seconds);

protected:

    void correctRight();

    void correctLeft();

    void correctUp();

    void correctDown();

};

