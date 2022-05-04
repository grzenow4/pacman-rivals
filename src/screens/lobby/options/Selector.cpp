#include "Selector.h"

unsigned int Selector::_next_available_selector_id = 1;
unsigned int Selector::_current_selector_id = 0;

Selector::Selector(sf::RenderWindow* window) {
    _window = window;

    _my_id = _next_available_selector_id;
    _next_available_selector_id++;
}
