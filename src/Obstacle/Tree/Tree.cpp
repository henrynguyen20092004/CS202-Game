#include "Tree.hpp"

#include "../../Random/Random.hpp"

Tree::Tree(TextureHolder& textureHolder)
    : Obstacle(
          textureHolder, Textures::ID::Tree,
          sf::IntRect(Random<int>::generate(0, 2) * 90, 0, 90, 90)
      ) {
    setHitbox(sf::FloatRect(10, 10, 70, 70));  // TODO: Set hitbox properly
}

Textures::ID Tree::getTextureID() const { return Textures::ID::Tree; }
