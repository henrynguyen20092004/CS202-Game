#include "PowerUpSettings.hpp"

PowerUpSettings::PowerUpSettings() {
    assignKey(sf::Keyboard::Num1, PowerUp::Type::Immortality);
    assignKey(sf::Keyboard::Num2, PowerUp::Type::SlowTime);
}

void PowerUpSettings::assignKey(sf::Keyboard::Key key, PowerUp::Type type) {
    for (auto pair : mKeyBinding) {
        if (pair.second == type) {
            mKeyBinding.erase(pair.first);
            break;
        }
    }

    mKeyBinding[key] = type;
}

PowerUp::Type PowerUpSettings::getPowerUpType(sf::Keyboard::Key key) const {
    if (mKeyBinding.find(key) != mKeyBinding.end()) {
        return mKeyBinding.at(key);
    }

    return PowerUp::Type::None;
}
