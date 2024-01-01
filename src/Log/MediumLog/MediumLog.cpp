#include "MediumLog.hpp"

MediumLog::MediumLog(TextureHolder& textureHolder, Directions::ID direction)
    : Log(textureHolder, Textures::ID::MediumLog, direction) {
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }
}

int MediumLog::getLength() const { return 2; }
