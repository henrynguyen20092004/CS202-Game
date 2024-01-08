#include "Rock.hpp"

Rock::Rock(TextureHolder& textureHolder)
    : Obstacle(textureHolder, Textures::ID::Rock) {
    setHitbox(sf::FloatRect(10, 10, 40, 45));
}

Textures::ID Rock::getTextureID() const { return Textures::ID::Rock; }
