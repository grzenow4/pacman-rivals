#include "../../src/coins/Coin.h"
#include "../../include/err.h"
#include "../../src/texture-holder/TextureHolder.h"
#include "../../src/sound-manager/SoundManager.h"
#include "../../include/game_constants.h"

int main() {
    TextureHolder textureHolder;
    SoundManager soundManager;

    Coin coin = Coin(0.f, 0.f);

    err::checkEqual(coin.isTaken(), false);

    coin.Take();

    err::checkEqual(coin.isTaken(), true);

    err::checkEqualFloat(coin.getSprite().getPosition().x, 0.f + (TILE_SIZE - COIN_SIZE) / 2);
    err::checkEqualFloat(coin.getSprite().getPosition().y, 0.f + (TILE_SIZE - COIN_SIZE) / 2);

    return 0;
}