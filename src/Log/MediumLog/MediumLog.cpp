#include "MediumLog.hpp"

MediumLog::MediumLog(TextureHolder& textureHolder, Directions::ID direction)
    : Log(textureHolder, Textures::ID::Log, sf::IntRect(90, 0, 180, 90),
          direction) {
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }
}

int MediumLog::getLength() const { return 2; }
