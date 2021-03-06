#include "RandomGhost.h"

#include "../../../include/random.h"
#include "../../texture-holder/TextureHolder.h"

RandomGhost::RandomGhost(std::shared_ptr<Map> map, int start_tile_x, int start_tile_y, int direction) {
    _map = std::move(map);

    _sprite = sf::Sprite(TextureHolder::GetTexture("../assets/graphics/ghosts/ghost-pink-1-right.png"));

    _sprite.setPosition(start_tile_x * TILE_SIZE, start_tile_y * TILE_SIZE);

    _direction = static_cast<Direction>(direction);
    _state = "1";
    _textureChange = 0.0;
}

Character::Direction RandomGhost::randNewDirection() {
    std::vector<Direction> directions;

    sf::Vector2i up_tile = getUpTile(), down_tile = getDownTile(), left_tile = getLeftTile(), right_tile = getRightTile();

    switch (_direction) {
        case LEFT:
            if (!_map.get()->getTiles()[left_tile.y][left_tile.x].isWall()) directions.push_back(LEFT);
            if (!_map.get()->getTiles()[up_tile.y][up_tile.x].isWall()) directions.push_back(UP);
            if (!_map.get()->getTiles()[down_tile.y][down_tile.x].isWall()) directions.push_back(DOWN);
            break;
        case RIGHT:
            if (!_map.get()->getTiles()[right_tile.y][right_tile.x].isWall()) directions.emplace_back(RIGHT);
            if (!_map.get()->getTiles()[down_tile.y][down_tile.x].isWall()) directions.emplace_back(DOWN);
            if (!_map.get()->getTiles()[up_tile.y][up_tile.x].isWall()) directions.emplace_back(UP);
            break;
        case UP:
            if (!_map.get()->getTiles()[up_tile.y][up_tile.x].isWall()) directions.emplace_back(UP);
            if (!_map.get()->getTiles()[right_tile.y][right_tile.x].isWall()) directions.emplace_back(RIGHT);
            if (!_map.get()->getTiles()[left_tile.y][left_tile.x].isWall()) directions.emplace_back(LEFT);
            break;
        case DOWN:
            if (!_map.get()->getTiles()[down_tile.y][down_tile.x].isWall()) directions.emplace_back(DOWN);
            if (!_map.get()->getTiles()[left_tile.y][left_tile.x].isWall()) directions.emplace_back(LEFT);
            if (!_map.get()->getTiles()[right_tile.y][right_tile.x].isWall()) directions.emplace_back(RIGHT);
            break;
        default:
            break;
    }

    if (directions.empty()) {
        return getOppositeDirection();
    } else {
        size_t rand_idx = random(0, (int) directions.size() - 1);
        return directions[rand_idx];
    }
}

void RandomGhost::animate(float dt_as_seconds) {
    _textureChange += dt_as_seconds;

    if (_textureChange >= 0.6){
        _textureChange -= 0.6;

        if (_state == "1"){
            _state = "2";
        }
        else {
            _state = "1";
        }
    }
    if (_direction == LEFT || _direction == UP){
        _sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/ghosts/ghost-pink-" + _state + "-left.png"));

    }
    else {
        _sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/ghosts/ghost-pink-" + _state + "-right.png"));
    }
}


void RandomGhost::update(float dt_as_seconds) {
    animate(dt_as_seconds);

    if (reachedNewTile(dt_as_seconds)) {
        Character::Direction new_direction = randNewDirection();

        move(dt_as_seconds);
       if (_direction != new_direction) {
            correct();
            _direction = new_direction;
            move(dt_as_seconds);
        }


    } else {
       move(dt_as_seconds);
    }
}

