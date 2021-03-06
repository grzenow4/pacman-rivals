#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <unordered_set>

#include "../Screen.h"
#include "../../level-manager/LevelManager.h"
#include "../../characters/player/Pacman.h"
#include "../../coins/Coin.h"
#include "PlayerInfo.h"
#include "PlayerInputHandler.h"
#include "PlayerStats.h"
#include "../../power-ups/PowerUpSpawner.h"
#include "../../power-ups/types/firing-bullet/Bullet.h"

class GameScreen : Screen {

private:

    sf::View _main_view; // view used for drawing game (map, characters, ...)

    LevelManager _level_manager;

    std::shared_ptr<Map> _grid;

    std::vector<std::shared_ptr<Ghost>> _ghosts;

    std::vector<PlayerInfo> _player_infos;

    std::vector<PlayerStats> _player_stats;

    std::vector<std::shared_ptr<Pacman>> _pacmans;

    std::vector<PlayerInputHandler> _player_input_handlers;

    std::unordered_map<int, Coin> _coins;

    PowerUpSpawner _power_up_spawner;
    std::unordered_set<std::shared_ptr<PowerUp>> _power_ups;

    std::unordered_set<std::shared_ptr<Bullet>> _bullets;
    std::unordered_set<std::shared_ptr<Bomb>> _bombs;

    std::unordered_set<std::shared_ptr<Spike>> _spikes;

    bool _new_map_needed = false;

    bool _is_paused = false;

    sf::Text _pause;
    sf::Text _continue;

    unsigned int _players_num = 0;

    unsigned int _rounds_left = 0;

    sf::Font _font;

    unsigned int _points_to_win;
    sf::Text _points_to_win_text;

    void loadNewMap();

    void handleCollisionsPP();
    void handleCollisionsPC();
    void handleCollisionsPG();
    void handleCollisionsPPU();
    void handleCollisionsBullets();
    void handleCollisionsBombs();
    void handleCollisionsSpikes();

    unsigned int alivePlayers() const;
    bool someoneWinsByPoints() const;
    void countPointsToWin();

    void rewardWinner();

public:

    GameScreen() = default;

    GameScreen(sf::RenderWindow* window, ScreenName* current_screen);

    void initialise(std::vector<PlayerInfo> player_infos, unsigned int rounds);

    void input() override;

    void update(float dt_as_seconds) override;

    void draw() override;

    const std::vector<PlayerInfo> & getPlayerInfos();

};
