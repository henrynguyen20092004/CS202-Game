#include "Car.hpp"

Car::Car(TextureHolder& textureHolder, Directions::ID direction)
    : Vehicle(textureHolder, Textures::ID::Car, direction) {
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }

    setHitbox(sf::FloatRect(10, 10, 180, 60));  // TODO: Set hitbox properly
}
