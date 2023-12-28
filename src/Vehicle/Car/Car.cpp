#include "Car.hpp"

Car::Car(TextureHolder& textureHolder, Directions::ID direction)
    : Vehicle(textureHolder, direction) {
    setSprite(Textures::ID::Car);
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }

    setHitbox(getLocalBounds());  // TODO: Set hitbox properly
}
