#include "LevelManager.h"

#include "../characters/ghosts/LinearGhost.h"
#include "../characters/ghosts/CycleGhost.h"
#include "../characters/ghosts/RandomGhost.h"
#include "../texture-holder/TextureHolder.h"
#include "../../include/random.h"

const int LevelManager::NUM_MAPS = 10;
const int LevelManager::NUM_COLORS = 10;

LevelManager::LevelManager() {
    _grid = std::make_shared<Map>();
    _played_maps = std::vector<bool>(NUM_MAPS, false);
    _loaded_level = -1;
}

std::shared_ptr<Map> LevelManager::getGrid() {
    return _grid;
}

std::vector<std::shared_ptr<Ghost>> &LevelManager::getGhosts() {
    return _ghosts;
}

std::vector<std::shared_ptr<Pacman>> &LevelManager::getPlayers() {
    return _pacmans;
}

void LevelManager::loadNewGrid() {
    std::ifstream myfile;
    myfile.open("../assets/maps/grids/grid" + std::to_string(_loaded_level) + ".txt");

    int color = random(1, NUM_COLORS - 1);

    if (myfile.is_open()) {
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                int tmp;
                myfile >> tmp;
                _grid->setTile(i, j, tmp, color);
            }
        }
        myfile.close();
    } else {
        std::cerr << "Can't find input file" << std::endl;
        exit(1);
    }
}

enum GhostEnum {
    LINEAR,
    CYCLE,
    RANDOM,
};

GhostEnum convert(const std::string& str) {
    if (str == "linear") return LINEAR;
    else if (str == "cycle") return CYCLE;
    else if (str == "random") return RANDOM;
    else return RANDOM;
}

void LevelManager::loadNewGhosts() {
    _ghosts.clear();
    std::ifstream myfile;
    myfile.open("../assets/maps/ghosts/ghosts" + std::to_string(_loaded_level) + ".txt");

    if (myfile.is_open()) {
        int size;
        myfile >> size;

        for (int k = 0; k < size; k++) {
            std::string type;
            int i, j, n;
            myfile >> type;
            GhostEnum ghost_type = convert(type);
            switch (ghost_type) {
                case LINEAR : {
                    myfile >> i >> j >> n;
                    _ghosts.emplace_back(std::static_pointer_cast<Ghost>(std::make_shared<LinearGhost>(_grid, i, j, n)));
                    break;
                }
                case CYCLE : {
                    myfile >> i >> j >> n;
                    std::vector<int> directions(n);
                    for (int l = 0; l < n; l++) {
                        myfile >> directions[l];
                    }
                    _ghosts.emplace_back(std::static_pointer_cast<Ghost>(std::make_shared<CycleGhost>(_grid, i, j, directions)));
                    break;
                }
                case RANDOM : {
                    myfile >> i >> j >> n;
                    _ghosts.emplace_back(std::static_pointer_cast<Ghost>(std::make_shared<RandomGhost>(_grid, i, j, n)));
                    break;
                }
            }
        }
        myfile.close();
    } else {
        std::cerr << "Can't find input file" << std::endl;
        exit(1);
    }
}

void LevelManager::loadNewPlayers() {
    _pacmans.clear();
    std::ifstream myfile;
    myfile.open("../assets/maps/players/players" + std::to_string(_loaded_level) + ".txt");

    if (myfile.is_open()) {
        for (int k = 0; k < 4; k++) {
            int i, j;
            myfile >> i >> j;
            _pacmans.emplace_back(std::make_shared<Pacman>(_grid, float(i) * TILE_SIZE, float(j) * TILE_SIZE));
        }
        myfile.close();
    } else {
        std::cerr << "Can't find input file" << std::endl;
        exit(1);
    }
}

void LevelManager::loadNewLevel() {
    std::vector<int> available_maps;
    for (int i = 0; i < NUM_MAPS; i++) {
        if (!_played_maps[i]) {
            available_maps.push_back(i + 1);
        }
    }
    _loaded_level = available_maps[random(0, (int) available_maps.size() - 1)];
    _played_maps[_loaded_level - 1] = true;

    loadNewGrid();
    loadNewPlayers();
    loadNewGhosts();
}

void LevelManager::initialise() {
    _played_maps.clear();
    std::fill(_played_maps.begin(), _played_maps.end(), false);
}

int LevelManager::getLoadedLevel() const {
    return _loaded_level;
}
