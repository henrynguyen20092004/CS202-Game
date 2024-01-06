#include "Pug.hpp"

Pug::Pug(
    TextureHolder& textureHolder, Textures::ID textureID,
    PowerUpList& powerUpList
)
    : Animal(textureHolder, textureID, powerUpList, 1, sf::seconds(1.f)) {
    setHitbox(getLocalBounds());  // TODO: Set hitbox properly
}

PowerUp::Type Pug::getPowerUpType() const { return PowerUp::Type::Immortality; }
