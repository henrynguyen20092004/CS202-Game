#include "Halo.hpp"

Halo::Halo(TextureHolder& textureHolder, Textures::ID textureID)
    : SpriteNode(textureHolder, textureID),
      mTextureRect(mSprite.getTextureRect()) {
    setPosition(-10, -10);
    hide();
}

void Halo::show() { setTextureRect(mTextureRect); }

void Halo::hide() { setTextureRect(sf::IntRect()); }
