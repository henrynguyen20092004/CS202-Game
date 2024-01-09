#include "Train.hpp"

Train::Train(
    TextureHolder& textureHolder, int seasonIndex, Directions::ID direction
)
    : Vehicle(textureHolder, Textures::ID::Train, sf::IntRect(), direction) {
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }

    setHitbox(getLocalBounds());
}

Textures::ID Train::getTextureID() const { return Textures::ID::Train; }
