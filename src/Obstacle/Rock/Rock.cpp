#include "Rock.hpp"

Rock::Rock(TextureHolder& textureHolder)
    : Obstacle(textureHolder, Textures::ID::Rock) {
    setHitbox(sf::FloatRect(10, 10, 60, 60));  // TODO: Set hitbox properly
}
