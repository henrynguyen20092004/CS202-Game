#include "Bus.hpp"

Bus::Bus(TextureHolder& textureHolder, Directions::ID direction)
    : Vehicle(textureHolder, Textures::ID::Bus, direction) {
    if (direction == Directions::ID::Left) {
        flipHorizontally();
    }

    setHitbox(sf::FloatRect(10, 10, 230, 70));  // TODO: Set hitbox properly
}
