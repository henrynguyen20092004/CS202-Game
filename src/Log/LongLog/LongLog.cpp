#include "LongLog.hpp"

LongLog::LongLog(TextureHolder& textureHolder, Directions::ID direction)
    : Log(textureHolder, Textures::ID::LongLog, direction) {
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }

    setHitbox(getLocalBounds());  // TODO: Set hitbox properly
}
