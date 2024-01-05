#include "ShortLog.hpp"

ShortLog::ShortLog(TextureHolder& textureHolder, Directions::ID direction)
    : Log(textureHolder, Textures::ID::Log, sf::IntRect(0, 0, 90, 90),
          direction) {
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }
}

int ShortLog::getLength() const { return 1; }
