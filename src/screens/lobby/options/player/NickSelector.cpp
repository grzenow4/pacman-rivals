#include "NickSelector.h"

NickSelector::NickSelector(sf::RenderWindow* window) : Selector(window) {

}

void NickSelector::input() {
    // TODO: letters and digits change _current_nickname
    // TODO: set _current_selector_id to _my_id
}

void NickSelector::update(float dt_as_seconds) {
    // Probably nothing to do.
}

void NickSelector::draw() {
    // TODO: draw this class (box with _current_nick)
}

std::string NickSelector::getCurrentNick() const {
    return _current_nick;
}