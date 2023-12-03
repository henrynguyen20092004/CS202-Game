#include "Animal.hpp"

Animal::Animal(TextureHolder& TextureHolder, Textures::ID textureID)
    : MovableSpriteNode(TextureHolder, textureID) {}
