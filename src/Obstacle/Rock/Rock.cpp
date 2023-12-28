#include "Rock.hpp"

Rock::Rock(TextureHolder& textureHolder) : Obstacle(textureHolder) {
    setSprite(Textures::ID::Rock);

    setHitbox(getLocalBounds());  // TODO: Set hitbox properly
}
