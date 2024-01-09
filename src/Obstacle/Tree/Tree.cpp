#include "Tree.hpp"

#include "../../Random/Random.hpp"

Tree::Tree(TextureHolder& textureHolder, int seasonIndex)
    : Obstacle(
          textureHolder, Textures::ID::Tree,
          sf::IntRect(
              Random<int>::generate(0, 2) * 90, seasonIndex * 90, 90, 90
          )
      ) {
    setHitbox(sf::FloatRect(10, 10, 70, 70));
}

Textures::ID Tree::getTextureID() const { return Textures::ID::Tree; }
