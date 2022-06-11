#include "Ghost.h"

sf::Vector2i Ghost::getUpTile() const {
    sf::FloatRect pos = getPosition();
    sf::Vector2i curr_tile = {(int) (pos.left / TILE_SIZE + 0.5), (int) (pos.top / TILE_SIZE + 0.5)};
    return {curr_tile.x, curr_tile.y - 1};
}

sf::Vector2i Ghost::getDownTile() const {
    sf::FloatRect pos = getPosition();
    sf::Vector2i curr_tile = {(int) (pos.left / TILE_SIZE + 0.5), (int) (pos.top / TILE_SIZE + 0.5)};
    return {curr_tile.x, curr_tile.y + 1};
}

sf::Vector2i Ghost::getLeftTile() const {
    sf::FloatRect pos = getPosition();
    sf::Vector2i curr_tile = {(int) (pos.left / TILE_SIZE + 0.5), (int) (pos.top / TILE_SIZE + 0.5)};
    return {curr_tile.x - 1, curr_tile.y};
}

sf::Vector2i Ghost::getRightTile() const {
    sf::FloatRect pos = getPosition();
    sf::Vector2i curr_tile = {(int) (pos.left / TILE_SIZE + 0.5), (int) (pos.top / TILE_SIZE + 0.5)};
    return {curr_tile.x + 1, curr_tile.y};
}
