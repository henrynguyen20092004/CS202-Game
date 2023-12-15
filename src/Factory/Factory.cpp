#include "Factory.hpp"

Factory::Factory(TextureHolder& textureHolder)
    : mTextureHolder(textureHolder) {}

void Factory::setVelocityPercent(float percent) {}

Directions::ID Factory::getDirection() const { return Directions::ID::None; }
