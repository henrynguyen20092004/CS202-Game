#include "Car.hpp"

Car::Car(TextureHolder& textureHolder, Directions::ID direction)
    : Vehicle(textureHolder, Textures::ID::Car, direction) {
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }

    setHitbox(getLocalBounds());  // TODO: Set hitbox properly
}
