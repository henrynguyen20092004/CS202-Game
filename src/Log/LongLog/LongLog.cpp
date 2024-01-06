#include "LongLog.hpp"

LongLog::LongLog(TextureHolder& textureHolder, Directions::ID direction)
    : Log(textureHolder, Textures::ID::Log, sf::IntRect(270, 0, 270, 90),
          direction) {
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }
}

int LongLog::getLength() const { return 3; }

Textures::ID LongLog::getTextureID() const { return Textures::ID::LongLog; }
