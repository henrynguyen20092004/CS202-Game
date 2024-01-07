#include "PowerUpList.hpp"

#include "../Global/Global.hpp"
#include "../PowerUp/Immortality/Immortality.hpp"
#include "../PowerUp/SlowTime/SlowTime.hpp"

PowerUpList::PowerUpList(
    PowerUpSettings& powerUpSettings, TextureHolder& textureHolder,
    FontHolder& fontHolder, sf::View& worldView, Player& player
)
    : mPowerUpSettings(powerUpSettings) {
    if (player.getPlayerNumber() == 1) {
        setPosition(Global::WINDOW_WIDTH - 2 * Global::TILE_SIZE - 40.f, 0.f);
    }

    initPowerUps(textureHolder, fontHolder, worldView, player);
}

void PowerUpList::addPowerUp(PowerUp::Type type) {
    mPowerUps[type]->increaseCount();
}

void PowerUpList::handleEventCurrent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        PowerUp::Type type = mPowerUpSettings.getPowerUpType(event.key.code);

        if (type != PowerUp::Type::None) {
            mPowerUps[type]->start();
        }
    }
}

void PowerUpList::initPowerUps(
    TextureHolder& textureHolder, FontHolder& fontHolder, sf::View& worldView,
    Player& player
) {
    PowerUpIconArgs defaultArgs(
        textureHolder, fontHolder, worldView, sf::Vector2f()
    );

    Immortality::Ptr immortality(new Immortality(defaultArgs, player));
    mPowerUps[PowerUp::Type::Immortality] = immortality.get();
    attachChild(std::move(immortality));

    defaultArgs.positionOffset.x += Global::TILE_SIZE;
    SlowTime::Ptr slowTime(new SlowTime(defaultArgs, player));
    mPowerUps[PowerUp::Type::SlowTime] = slowTime.get();
    attachChild(std::move(slowTime));
}
