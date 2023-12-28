#include "Rock.hpp"

Rock::Rock(TextureHolder& textureHolder)
    : Obstacle(textureHolder, Textures::ID::Rock) {
    setHitbox(getLocalBounds());  // TODO: Set hitbox properly
}
