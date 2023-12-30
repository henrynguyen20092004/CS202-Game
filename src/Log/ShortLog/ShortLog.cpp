#include "ShortLog.hpp"

ShortLog::ShortLog(TextureHolder& textureHolder, Directions::ID direction)
    : Log(textureHolder, Textures::ID::ShortLog, direction) {
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }
}

int ShortLog::getLength() const { return 1; }
