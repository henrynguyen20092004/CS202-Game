#include "PlayerSettings.hpp"

PlayerSettings::PlayerSettings() {
    assignKey(sf::Keyboard::Up, Directions::ID::Up);
    assignKey(sf::Keyboard::Down, Directions::ID::Down);
    assignKey(sf::Keyboard::Left, Directions::ID::Left);
    assignKey(sf::Keyboard::Right, Directions::ID::Right);
}

void PlayerSettings::assignKey(
    sf::Keyboard::Key key, Directions::ID direction
) {
    for (auto pair : mKeyBinding) {
        if (pair.second == direction) {
            mKeyBinding.erase(pair.first);
            break;
        }
    }

    mKeyBinding[key] = direction;
}

Directions::ID PlayerSettings::getDirection(sf::Keyboard::Key key) const {
    if (mKeyBinding.find(key) != mKeyBinding.end()) {
        return mKeyBinding.at(key);
    }

    return Directions::ID::None;
}
