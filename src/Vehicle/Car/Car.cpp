#include "Car.hpp"

Car::Car(
    TextureHolder& textureHolder, int seasonIndex, Directions::ID direction
)
    : Vehicle(textureHolder, Textures::ID::Car, sf::IntRect(), direction) {
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }

    setHitbox(sf::FloatRect(10, 10, 130, 60));
}

Textures::ID Car::getTextureID() const { return Textures::ID::Car; }
