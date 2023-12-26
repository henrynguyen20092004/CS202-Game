#include "PowerUpList.hpp"

#include "../Global/Global.hpp"
#include "../PowerUp/Immortality/Immortality.hpp"
#include "../PowerUp/Regenerate/Regenerate.hpp"
#include "../PowerUp/SlowTime/SlowTime.hpp"

PowerUpList::PowerUpList(
    PowerUpSettings& powerUpSettings, TextureHolder& textureHolder,
    const FontHolder& fontHolder, sf::View& worldView, Player& player
)
    : mPowerUpSettings(powerUpSettings) {
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
    TextureHolder& textureHolder, const FontHolder& fontHolder,
    sf::View& worldView, Player& player
) {
    sf::Vector2f positionOffset = sf::Vector2f();

    Immortality::Ptr immortality(new Immortality(
        PowerUpIconArgs(textureHolder, fontHolder, worldView, positionOffset),
        player
    ));
    mPowerUps[PowerUp::Type::Immortality] = immortality.get();
    attachChild(std::move(immortality));

    positionOffset.x += Global::TILE_SIZE * 1.25f;

    Regenerate::Ptr regenerate(new Regenerate(
        PowerUpIconArgs(textureHolder, fontHolder, worldView, positionOffset),
        player
    ));
    mPowerUps[PowerUp::Type::Regenerate] = regenerate.get();
    attachChild(std::move(regenerate));

    positionOffset.x += Global::TILE_SIZE * 1.25f;

    SlowTime::Ptr slowTime(new SlowTime(
        PowerUpIconArgs(textureHolder, fontHolder, worldView, positionOffset),
        player
    ));
    mPowerUps[PowerUp::Type::SlowTime] = slowTime.get();
    attachChild(std::move(slowTime));
}
