#include "Factory.hpp"

Factory::Factory(TextureHolder& textureHolder)
    : mTextureHolder(textureHolder) {}

Directions::ID Factory::getDirection() const { return Directions::ID::None; }
