#include "PlayerSettings.hpp"

#include "../FileIO/FileIO.hpp"

PlayerSettings::PlayerSettings(bool isPlayer2) { setToDefault(isPlayer2); }

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

sf::Keyboard::Key PlayerSettings::getAssignedKey(Directions::ID direction
) const {
    for (auto pair : mKeyBinding) {
        if (pair.second == direction) {
            return pair.first;
        }
    }

    return sf::Keyboard::Unknown;
}

void PlayerSettings::setToDefault(bool isPlayer2) {
    if (isPlayer2) {
        assignKey(sf::Keyboard::Up, Directions::ID::Up);
        assignKey(sf::Keyboard::Down, Directions::ID::Down);
        assignKey(sf::Keyboard::Left, Directions::ID::Left);
        assignKey(sf::Keyboard::Right, Directions::ID::Right);
    } else {
        assignKey(sf::Keyboard::W, Directions::ID::Up);
        assignKey(sf::Keyboard::S, Directions::ID::Down);
        assignKey(sf::Keyboard::A, Directions::ID::Left);
        assignKey(sf::Keyboard::D, Directions::ID::Right);
    }
}

void PlayerSettings::save(std::ofstream& fout) const {
    fout << mKeyBinding.size() << '\n';

    for (auto pair : mKeyBinding) {
        fout << pair.first << ' ' << static_cast<int>(pair.second) << '\n';
    }
}

void PlayerSettings::load(std::ifstream& fin) {
    sf::Keyboard::Key key;
    int size, direction;

    fin >> size;

    for (int i = 0; i < size; ++i) {
        fin >> key >> direction;
        assignKey(key, static_cast<Directions::ID>(direction));
    }
}
