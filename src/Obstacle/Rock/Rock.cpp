#include "Rock.hpp"

Rock::Rock(TextureHolder& textureHolder, int seasonIndex)
    : Obstacle(
          textureHolder, Textures::ID::Rock,
          sf::IntRect(0, seasonIndex * 60, 60, 60)
      ) {
    setHitbox(sf::FloatRect(10, 10, 40, 45));
}

Textures::ID Rock::getTextureID() const { return Textures::ID::Rock; }
