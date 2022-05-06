#pragma once

#include "../Selector.h"
#include "../../buttons/ButtonAD.h"


class PlayersSelector : Selector {

private:

    unsigned int _current_players = 2;

    sf::Text _number;

    sf::Font _font;

    sf::Sprite _border;

public:

    ButtonAD _A;

    ButtonAD _D;

    PlayersSelector() = default;

    PlayersSelector(sf::RenderWindow* window);

    void input() override;

    void update(float dt_as_seconds) override;

    void draw() override;

    unsigned int getCurrentPlayers() const;

};