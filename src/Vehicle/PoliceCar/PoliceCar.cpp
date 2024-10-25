#include "PoliceCar.hpp"

PoliceCar::PoliceCar(TextureHolder& textureHolder, Directions::ID direction)
    : Vehicle(textureHolder, Textures::ID::PoliceCar, direction) {
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }

    setHitbox(sf::FloatRect(10, 10, 130, 60));
}

Textures::ID PoliceCar::getTextureID() const { return Textures::ID::PoliceCar; }
