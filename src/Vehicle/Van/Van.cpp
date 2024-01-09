#include "Van.hpp"

Van::Van(
    TextureHolder& textureHolder, int seasonIndex, Directions::ID direction
)
    : Vehicle(textureHolder, Textures::ID::Van, sf::IntRect(), direction) {
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }

    setHitbox(sf::FloatRect(10, 10, 90, 60));
}

Textures::ID Van::getTextureID() const { return Textures::ID::Van; }
