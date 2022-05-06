#pragma once

#include <string>

#include "../Selector.h"

class NickSelector : Selector {

private:

    std::string _current_nick;

public:

    NickSelector() = default;

    NickSelector(sf::RenderWindow* window);

    void input() override;

    void update(float dt_as_seconds) override;

    void draw() override;

    std::string getCurrentNick() const;

};