#include "PowerUpSettings.hpp"

#include "../FileIO/FileIO.hpp"

PowerUpSettings::PowerUpSettings(bool isPlayer2) { setToDefault(isPlayer2); }

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

sf::Keyboard::Key PowerUpSettings::getAssignedKey(PowerUp::Type type) const {
    for (auto pair : mKeyBinding) {
        if (pair.second == type) {
            return pair.first;
        }
    }

    return sf::Keyboard::Unknown;
}

void PowerUpSettings::setToDefault(bool isPlayer2) {
    if (isPlayer2) {
        assignKey(sf::Keyboard::K, PowerUp::Type::Immortality);
        assignKey(sf::Keyboard::L, PowerUp::Type::SlowTime);
    } else {
        assignKey(sf::Keyboard::Num1, PowerUp::Type::Immortality);
        assignKey(sf::Keyboard::Num2, PowerUp::Type::SlowTime);
    }
}

void PowerUpSettings::save(std::ofstream& fout) const {
    fout << mKeyBinding.size() << '\n';

    for (auto pair : mKeyBinding) {
        fout << pair.first << ' ' << pair.second << '\n';
    }
}

void PowerUpSettings::load(std::ifstream& fin) {
    sf::Keyboard::Key key;
    int size, type;

    fin >> size;

    for (int i = 0; i < size; ++i) {
        fin >> key >> type;
        assignKey(key, static_cast<PowerUp::Type>(type));
    }
}
