#include "Train.hpp"

Train::Train(TextureHolder& textureHolder, Directions::ID direction)
    : Vehicle(textureHolder, direction) {
    setSprite(Textures::ID::Train);
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }

    setHitbox(getLocalBounds());  // TODO: Set hitbox properly
}
