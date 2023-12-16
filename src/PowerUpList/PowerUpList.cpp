#include "PowerUpList.hpp"

#include "../PowerUp/BonusHealth/BonusHealth.hpp"
#include "../PowerUp/Immortality/Immortality.hpp"
#include "../PowerUp/Jump/Jump.hpp"
#include "../PowerUp/SlowTime/SlowTime.hpp"

PowerUpList::PowerUpList(Player& player, PowerUpSettings& powerUpSettings)
    : mPowerUpSettings(powerUpSettings) {
    initPowerUps(player);
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

void PowerUpList::updateCurrent(sf::Time deltaTime) {
    for (auto& powerUp : mPowerUps) {
        powerUp.second->update(deltaTime);
    }
}

void PowerUpList::initPowerUps(Player& player) {
    mPowerUps[PowerUp::Type::BonusHealth] =
        std::make_unique<BonusHealth>(player);
    mPowerUps[PowerUp::Type::Immortality] =
        std::make_unique<Immortality>(player);
    mPowerUps[PowerUp::Type::Jump] = std::make_unique<Jump>(player);
    mPowerUps[PowerUp::Type::SlowTime] = std::make_unique<SlowTime>(player);
}
