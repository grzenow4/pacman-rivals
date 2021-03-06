#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "../../../map/Map.h"

class Spike {

private:

    sf::Sprite _sprite;

    unsigned int _user;

    bool _disappeared = false;

public:

    Spike() = default;

    Spike(sf::Vector2f position, unsigned int user);

    sf::FloatRect getPosition() const;

    const sf::Sprite &getSprite() const;

    unsigned int getUser() const;

    void disappear();

    bool disappeared() const;

    void update(float dt_as_seconds);

};
