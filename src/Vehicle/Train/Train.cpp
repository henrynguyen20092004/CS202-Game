#include "Train.hpp"

Train::Train(TextureHolder& textureHolder, Directions::ID direction)
    : Vehicle(textureHolder, Textures::ID::Train, direction) {
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }

    setHitbox(getLocalBounds());
}

Textures::ID Train::getTextureID() const { return Textures::ID::Train; }
